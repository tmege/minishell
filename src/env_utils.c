/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_env_index(char *name, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0
			&& (envp[i][len] == '=' || envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static char	*make_env_entry(char *name, char *value)
{
	char	*tmp;
	char	*entry;

	tmp = ft_strjoin(name, "=");
	entry = ft_strjoin(tmp, value);
	free(tmp);
	return (entry);
}

void	add_env_entry(char *entry, t_data *data)
{
	int		count;
	char	**new_envp;
	int		i;

	count = 0;
	while (data->envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
	{
		free(entry);
		return ;
	}
	i = -1;
	while (++i < count)
		new_envp[i] = data->envp[i];
	new_envp[count] = entry;
	new_envp[count + 1] = NULL;
	free(data->envp);
	data->envp = new_envp;
}

void	set_env_value(char *name, char *value, t_data *data)
{
	int		idx;
	char	*entry;

	entry = make_env_entry(name, value);
	idx = find_env_index(name, data->envp);
	if (idx >= 0)
	{
		free(data->envp[idx]);
		data->envp[idx] = entry;
	}
	else
		add_env_entry(entry, data);
}

void	remove_env_value(char *name, t_data *data)
{
	int	idx;
	int	i;

	idx = find_env_index(name, data->envp);
	if (idx < 0)
		return ;
	free(data->envp[idx]);
	i = idx;
	while (data->envp[i + 1])
	{
		data->envp[i] = data->envp[i + 1];
		i++;
	}
	data->envp[i] = NULL;
}
