/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:26:05 by rboland           #+#    #+#             */
/*   Updated: 2025/01/30 12:15:55 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*  affiche le message d erreur en parametre sur la sortie erreur
*   et exit le programme.
*/

void	error_exit(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

/*  Verifie si le nombre d argument est correcte ainsi que
*   la lisibilite d infile et outfile
*/

int	arg_check(int argc, char **argv, int *infile, int *outfile)
{
	if (argc != 5)
	{
		ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(EXIT_FAILURE);
	}
	(*infile) = open(argv[1], O_RDONLY);
	if ((*infile) < 0)
		error_exit("Error opening infile");
	(*outfile) = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*outfile) < 0)
		error_exit("Error opening outfile");
	return (0);
}

/*  Boucle sur chaque string de envp jusqu a trouver une string contenant
*   "PATH=" dans les 5 premier caractere et retourne un pointeur vers 
*   la position de cette string+5 char (C est a dire la string entiere sauf 
*   "PATH="). Retourne NULL si ne trouve pas la variable PATH.
*/

char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/*	Trouve le chemin complet de la commande dans le PATH,
*	retourne NULL si non trouvé.
*/

char	*find_command_path(char *cmd, char **envp)
{
	char	*path;
	char	**paths;
	char	*full_path;
	int		i;

	path = get_path_from_env(envp);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	i = 0;
	while (paths && paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

/* Exécute la commande avec les arguments appropriés et l'environnement. */

void	execute_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args)
		error_exit("malloc failed");
	*cmd_path = find_command_path(args[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		exit(EXIT_FAILURE);
	}
	execve(cmd_path, args, envp);
	error_exit("execve failed");
}

int main(int argc, char **argv, char **envp)
{
    int     pipe_fd[2];
    pid_t   pid1;
    pid_t   pid2;
    int     infile;
    int     outfile;
    
    arg_check(argc, argv, &infile, &outfile);
    if (pipe(pipe_fd) == -1)
        error_exit("pipe failed");
    pid1 = fork();
    if (pid1 == -1)
        error_exit("fork failed");
    if (pid1 == 0) // Processus enfant 1
    {
        dup2(infile, STDIN_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execute_cmd(argv[2], envp);
    }
    pid2 = fork();
    if (pid2 == -1)
        error_exit("fork failed");
    if (pid2 == 0) // Processus enfant 2
    {
        dup2(pipe_fd[0], STDIN_FILENO);
        dup2(outfile, STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execute_cmd(argv[3], envp);
    }
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(infile);
    close(outfile);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}
