/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

static char	**dup_envp(char **envp)
{
	char	**new;
	int		count;
	int		i;

	count = count_strs(envp);
	new = malloc(sizeof(char *) * (count + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new[i] = ft_strdup(envp[i]);
		if (!new[i])
		{
			while (--i >= 0)
				free(new[i]);
			free(new);
			return (NULL);
		}
		i++;
	}
	new[count] = NULL;
	return (new);
}

void	init_shell(t_data *data, char **envp)
{
	data->envp = dup_envp(envp);
	data->exit_status = 0;
	data->running = 1;
	data->in_pipe = 0;
	data->cmds = NULL;
	setup_completion();
}

void	cleanup_shell(t_data *data)
{
	free_envp(data->envp);
	rl_clear_history();
}
