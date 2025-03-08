/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <romain.boland@hotmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:44:04 by rboland           #+#    #+#             */
/*   Updated: 2025/03/08 10:56:41 by rboland          ###   ########.fr       */
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

// exec.c
void    execute_cmd(char *cmd, char **envp);

// error.c
void	error_exit(char *msg);
void	ft_free_split(char **tab);

// path.c
char	*find_command_path(char *cmd, char **envp);

#endif