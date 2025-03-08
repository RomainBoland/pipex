/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <romain.boland@hotmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:26:05 by rboland           #+#    #+#             */
/*   Updated: 2025/03/08 11:14:25 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*  Check numbers of args and also if we can open
*   infile and outfile. if outfile doesnt exist, it creates it
*/

void	arg_check(int argc, char **argv, int *infile, int *outfile)
{
	if (argc != 5)
	{
		ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(EXIT_FAILURE);
	}
	(*infile) = open(argv[1], O_RDONLY);
	if ((*infile) < 0)
	{
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		(*infile) = open("/dev/null", O_RDONLY);
	}
	(*outfile) = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*outfile) < 0)
		error_exit("Error opening outfile");
}

/*	Configure fd and replace via dup2 and
*	close files we dont need anymore and then
*	execute command
*/

void	handle_child(int fd_in, int fd_out, char *cmd, char **envp)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	execute_cmd(cmd, envp);
}

/*	Create child processes with fork and call handle_child in each
*	process with adapted fd to link pipe and files
*/

void	process_children(int *pipe_fd, char **argv, char **envp, t_files files)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
		error_exit("fork failed");
	if (pid1 == 0)
	{
		close(pipe_fd[0]);
		handle_child(files.infile, pipe_fd[1], argv[2], envp);
	}
	pid2 = fork();
	if (pid2 == -1)
		error_exit("fork failed");
	if (pid2 == 0)
	{
		close(pipe_fd[1]);
		handle_child(pipe_fd[0], files.outfile, argv[3], envp);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

/*	Create de pipe and calls children.
*/

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	t_files	files;

	arg_check(argc, argv, &files.infile, &files.outfile);
	if (pipe(pipe_fd) == -1)
		error_exit("pipe failed");
	process_children(pipe_fd, argv, envp, files);
	close(files.infile);
	close(files.outfile);
	return (0);
}
