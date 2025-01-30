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