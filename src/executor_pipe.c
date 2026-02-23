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

/* st[0]=prev_read st[1]=pipe_read st[2]=pipe_write st[3]=i st[4]=n */

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

static int	pipe_fork_one(t_cmd **cmd, t_data *data, int *st, pid_t *pids)
{
	if (st[3] < st[4] - 1 && pipe(st + 1) < 0)
	{
		perror("minishell");
		return (-1);
	}
	pids[st[3]] = fork();
	if (pids[st[3]] == 0)
		pipe_child(*cmd, data, st, st[3] == st[4] - 1);
	if (st[0] != -1)
		close(st[0]);
	if (st[3] < st[4] - 1)
	{
		close(st[2]);
		st[0] = st[1];
	}
	else
		st[0] = -1;
	*cmd = (*cmd)->next;
	return (0);
}

void	execute_pipeline(t_data *data)
{
	pid_t	*pids;
	t_cmd	*cmd;
	int		st[5];

	st[4] = count_cmds(data->cmds);
	pids = malloc(sizeof(pid_t) * st[4]);
	if (!pids)
		return ;
	setup_signals_exec();
	st[0] = -1;
	cmd = data->cmds;
	st[3] = -1;
	while (++st[3] < st[4])
	{
		if (pipe_fork_one(&cmd, data, st, pids) < 0)
			break ;
	}
	wait_children(pids, st[4], data);
	free(pids);
}
