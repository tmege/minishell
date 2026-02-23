/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_dollar(char *str, int *i, t_data *data)
{
	char	*name;
	char	*val;
	int		start;

	(*i)++;
	if (str[*i] == '{')
	{
		(*i)++;
		start = *i;
		while (str[*i] && str[*i] != '}')
			(*i)++;
		if (!str[*i])
			return (ft_strdup("${"));
		name = ft_substr(str, start, *i - start);
		(*i)++;
		val = get_env_value(name, data);
		free(name);
		return (val);
	}
	name = extract_var_name(str, i);
	if (!name)
		return (ft_strdup("$"));
	val = get_env_value(name, data);
	free(name);
	return (val);
}

static char	*process_dq_char(char *str, int *i, t_data *data, char *res)
{
	char	*exp;

	if (str[*i] == '\\' && str[*i + 1]
		&& ft_strchr("\"\\$`\n", str[*i + 1]))
	{
		(*i)++;
		return (append_char(res, str[(*i)++]));
	}
	if (str[*i] == '$' && str[*i + 1]
		&& str[*i + 1] != '"' && str[*i + 1] != ' ')
	{
		exp = expand_dollar(str, i, data);
		res = append_str(res, exp);
		free(exp);
		return (res);
	}
	return (append_char(res, str[(*i)++]));
}

static char	*expand_dq(char *str, int *i, t_data *data)
{
	char	*result;

	result = NULL;
	(*i)++;
	while (str[*i] && str[*i] != '"')
		result = process_dq_char(str, i, data, result);
	if (str[*i] == '"')
		(*i)++;
	if (!result)
		return (ft_strdup(""));
	return (result);
}

static char	*expand_chunk(char *str, int *i, t_data *data)
{
	if (str[*i] == '\'')
		return (expand_single_quotes(str, i));
	if (str[*i] == '"')
		return (expand_dq(str, i, data));
	if (str[*i] == '$' && str[*i + 1]
		&& (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_'
			|| str[*i + 1] == '?' || str[*i + 1] == '{'))
		return (expand_dollar(str, i, data));
	return (NULL);
}

char	*expand_value(char *str, t_data *data, int quoted)
{
	char	*result;
	char	*expanded;
	int		i;

	result = NULL;
	i = 0;
	(void)quoted;
	while (str[i])
	{
		expanded = expand_chunk(str, &i, data);
		if (expanded)
		{
			result = append_str(result, expanded);
			free(expanded);
		}
		else
			result = append_char(result, str[i++]);
	}
	if (!result)
		result = ft_strdup("");
	return (result);
}
