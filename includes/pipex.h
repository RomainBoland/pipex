/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <rboland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:44:04 by rboland           #+#    #+#             */
/*   Updated: 2025/01/30 13:07:53 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>

typedef struct s_files
{
	int	infile;
	int	outfile;
}	t_files;

// error.c
void	error_exit(char *msg);
void	ft_free_split(char **tab);

// path.c
char	*find_command_path(char *cmd, char **envp);
char	*get_path_from_env(char **envp);

#endif