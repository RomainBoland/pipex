/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:01:48 by rboland           #+#    #+#             */
/*   Updated: 2025/01/30 13:01:48 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

int	is_valid_cmd(char *cmd)
{
	if (!cmd || cmd[0] == '\0')
		return (0);
	return (1);
}

char	*build_cmd_path(char *dir_path, char *cmd)
{
	char	*temp_path;
	char	*full_path;

	temp_path = ft_strjoin(dir_path, "/");
	if (!temp_path)
		return (NULL);
	full_path = ft_strjoin(temp_path, cmd);
	free(temp_path);
	return (full_path);
}

char	*search_cmd_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths && paths[i])
	{
		full_path = build_cmd_path(paths[i], cmd);
		if (!full_path)
		{
			ft_free_split(paths);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	*path;
	char	**paths;
	char	*full_path;

	if (!is_valid_cmd(cmd))
		return (NULL);
	path = get_path_from_env(envp);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	full_path = search_cmd_in_paths(paths, cmd);
	if (full_path)
		return (full_path);
	ft_free_split(paths);
	return (NULL);
}
