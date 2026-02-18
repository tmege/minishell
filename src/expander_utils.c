/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *s, char c)
{
	char	buf[2];
	char	*res;

	buf[0] = c;
	buf[1] = '\0';
	if (!s)
		return (ft_strdup(buf));
	res = ft_strjoin(s, buf);
	free(s);
	return (res);
}

char	*append_str(char *s, char *add)
{
	char	*res;

	if (!add)
		return (s);
	if (!s)
		return (ft_strdup(add));
	res = ft_strjoin(s, add);
	free(s);
	return (res);
}

char	*extract_var_name(char *str, int *i)
{
	int	start;

	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (NULL);
	return (ft_substr(str, start, *i - start));
}

char	*get_env_value(char *name, t_data *data)
{
	int		i;
	int		len;

	if (!name)
		return (NULL);
	if (ft_strncmp(name, "?", 2) == 0)
		return (ft_itoa(data->exit_status));
	len = ft_strlen(name);
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], name, len) == 0
			&& data->envp[i][len] == '=')
			return (ft_strdup(data->envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}
