/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboland <romain.boland@hotmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:46:54 by rboland           #+#    #+#             */
/*   Updated: 2025/03/08 11:16:58 by rboland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_command(char *cmd)
{
	if (!cmd || cmd[0] == '\0')
	{
		ft_putendl_fd("Error: empty command", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	handle_invalid_args(char **args)
{
	if (!args || !args[0])
	{
		ft_putendl_fd("Error: invalid command", STDERR_FILENO);
		if (args)
			ft_free_split(args);
		exit(EXIT_FAILURE);
	}
}

void	handle_cmd_not_found(char **args)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putendl_fd(args[0], 2);
	ft_free_split(args);
	exit(EXIT_FAILURE);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	check_command(cmd);
	args = ft_split(cmd, ' ');
	handle_invalid_args(args);
	cmd_path = find_command_path(args[0], envp);
	if (!cmd_path)
		handle_cmd_not_found(args);
	execve(cmd_path, args, envp);
	free(cmd_path);
	ft_free_split(args);
	error_exit("execve failed");
}
