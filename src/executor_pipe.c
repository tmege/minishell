/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/21 00:00:00 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* fds[0]=prev_read  fds[1]=new_pipe_read  fds[2]=new_pipe_write */

static void	pipe_child_setup(int *fds, int is_last)
{
	if (fds[0] != -1)
		dup2(fds[0], STDIN_FILENO);
	if (!is_last)
		dup2(fds[2], STDOUT_FILENO);
	if (fds[0] != -1)
		close(fds[0]);
	if (!is_last)
	{
		close(fds[1]);
		close(fds[2]);
	}
}

static void	pipe_child(t_cmd *cmd, t_data *data, int *fds, int is_last)
{
	int	ret;

	data->in_pipe = 1;
	setup_signals_child();
	pipe_child_setup(fds, is_last);
	if (apply_redirections(cmd) != 0)
	{
		free_cmds(data->cmds);
		free_envp(data->envp);
		exit(1);
	}
	if (!cmd->args)
	{
		free_cmds(data->cmds);
		free_envp(data->envp);
		exit(0);
	}
	if (is_builtin(cmd->args[0]))
	{
		ret = exec_builtin(cmd, data);
		free_cmds(data->cmds);
		free_envp(data->envp);
		exit(ret);
	}
	pipe_exec_cmd(cmd, data);
}

static void	pipe_parent_update(int *fds, int is_last)
{
	if (fds[0] != -1)
		close(fds[0]);
	if (!is_last)
	{
		close(fds[2]);
		fds[0] = fds[1];
	}
	else
		fds[0] = -1;
}

static void	wait_children(pid_t *pids, int n, t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		if (i == n - 1)
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
		i++;
	}
}

void	execute_pipeline(t_data *data)
{
	pid_t	*pids;
	t_cmd	*cmd;
	int		fds[3];
	int		info[2];

	info[1] = count_cmds(data->cmds);
	pids = malloc(sizeof(pid_t) * info[1]);
	if (!pids)
		return ;
	setup_signals_exec();
	fds[0] = -1;
	cmd = data->cmds;
	info[0] = -1;
	while (++info[0] < info[1])
	{
		if (info[0] < info[1] - 1 && pipe(fds + 1) < 0)
		{
			perror("minishell");
			break ;
		}
		pids[info[0]] = fork();
		if (pids[info[0]] == 0)
			pipe_child(cmd, data, fds, info[0] == info[1] - 1);
		pipe_parent_update(fds, info[0] == info[1] - 1);
		cmd = cmd->next;
	}
	wait_children(pids, info[1], data);
	free(pids);
}
