/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

static int	**create_pipes(int n)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * n);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < n)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) < 0)
			return (NULL);
		i++;
	}
	return (pipes);
}

static void	pipe_child(t_cmd *cmd, t_data *data, int **pipes, int *info)
{
	int	idx;
	int	n;
	int	ret;

	idx = info[0];
	n = info[1];
	data->in_pipe = 1;
	setup_signals_child();
	if (idx > 0)
		dup2(pipes[idx - 1][0], STDIN_FILENO);
	if (idx < n - 1)
		dup2(pipes[idx][1], STDOUT_FILENO);
	close_pipes(pipes, n - 1);
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

void	execute_pipeline(t_data *data)
{
	int		**pipes;
	pid_t	*pids;
	t_cmd	*cmd;
	int		info[2];

	info[1] = count_cmds(data->cmds);
	pipes = create_pipes(info[1] - 1);
	pids = malloc(sizeof(pid_t) * info[1]);
	if (!pipes || !pids)
		return ;
	setup_signals_exec();
	cmd = data->cmds;
	info[0] = -1;
	while (++info[0] < info[1])
	{
		pids[info[0]] = fork();
		if (pids[info[0]] == 0)
			pipe_child(cmd, data, pipes, info);
		cmd = cmd->next;
	}
	close_pipes(pipes, info[1] - 1);
	wait_children(pids, info[1], data);
	free(pids);
}
