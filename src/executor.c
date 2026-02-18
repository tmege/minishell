/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_status(int status, t_data *data)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(2, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		data->exit_status = 128 + WTERMSIG(status);
	}
	else
		data->exit_status = WEXITSTATUS(status);
}

static void	exec_external(t_cmd *cmd, t_data *data, char *path)
{
	pid_t	pid;
	int		status;

	setup_signals_exec();
	pid = fork();
	if (pid == 0)
	{
		setup_signals_child();
		if (apply_redirections(cmd) != 0)
			exit(1);
		execve(path, cmd->args, data->envp);
		perror("minishell");
		exit(126);
	}
	free(path);
	waitpid(pid, &status, 0);
	handle_child_status(status, data);
}

static void	exec_redir_cmd(t_cmd *cmd, t_data *data)
{
	int	saved[2];

	saved[0] = dup(STDIN_FILENO);
	saved[1] = dup(STDOUT_FILENO);
	if (apply_redirections(cmd) == 0)
	{
		if (cmd->args)
			data->exit_status = exec_builtin(cmd, data);
		else
			data->exit_status = 0;
	}
	else
		data->exit_status = 1;
	dup2(saved[0], STDIN_FILENO);
	dup2(saved[1], STDOUT_FILENO);
	close(saved[0]);
	close(saved[1]);
}

static void	exec_single(t_cmd *cmd, t_data *data)
{
	char	*path;

	if (!cmd->args || is_builtin(cmd->args[0]))
	{
		exec_redir_cmd(cmd, data);
		return ;
	}
	if (ft_strchr(cmd->args[0], '/'))
		path = resolve_path_cmd(cmd->args[0], data);
	else
		path = find_cmd_path(cmd->args[0], data->envp);
	if (!path)
		return ;
	exec_external(cmd, data, path);
}

void	execute_cmds(t_data *data)
{
	if (!data->cmds)
		return ;
	if (collect_heredocs(data->cmds, data) != 0)
	{
		data->exit_status = 130;
		return ;
	}
	if (count_cmds(data->cmds) == 1)
		exec_single(data->cmds, data);
	else
		execute_pipeline(data);
}
