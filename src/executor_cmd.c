/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	path_error_msg(char *cmd, char *msg, int code, t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	data->exit_status = code;
}

void	cmd_path_error(char *cmd, t_data *data)
{
	struct stat	sb;

	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
			path_error_msg(cmd, ": Is a directory\n", 126, data);
		else if (access(cmd, F_OK) == 0)
			path_error_msg(cmd, ": Permission denied\n", 126, data);
		else
			path_error_msg(cmd, ": No such file or directory\n", 127, data);
		return ;
	}
	path_error_msg(cmd, ": command not found\n", 127, data);
}

char	*resolve_path_cmd(char *cmd, t_data *data)
{
	struct stat	sb;

	if (stat(cmd, &sb) != 0)
	{
		cmd_path_error(cmd, data);
		return (NULL);
	}
	if (S_ISDIR(sb.st_mode) || access(cmd, X_OK) != 0)
	{
		cmd_path_error(cmd, data);
		return (NULL);
	}
	return (ft_strdup(cmd));
}

void	pipe_exec_cmd(t_cmd *cmd, t_data *data)
{
	char	*path;

	if (ft_strchr(cmd->args[0], '/'))
		path = resolve_path_cmd(cmd->args[0], data);
	else
		path = find_cmd_path(cmd->args[0], data->envp);
	if (path)
	{
		execve(path, cmd->args, data->envp);
		perror("minishell");
		free_cmds(data->cmds);
		free_envp(data->envp);
		free(path);
		exit(126);
	}
	if (!ft_strchr(cmd->args[0], '/'))
		cmd_path_error(cmd->args[0], data);
	free_cmds(data->cmds);
	free_envp(data->envp);
	exit(data->exit_status);
}

int	exec_builtin(t_cmd *cmd, t_data *data)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (builtin_echo(cmd->args));
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (builtin_cd(cmd->args, data));
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (builtin_export(cmd->args, data));
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (builtin_unset(cmd->args, data));
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (builtin_env(data));
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (builtin_exit(cmd->args, data));
	if (ft_strncmp(cmd->args[0], ".", 2) == 0)
		return (builtin_dot(cmd->args));
	return (1);
}
