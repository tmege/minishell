/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/28 00:00:00 by tmege            ###   ########.fr       */
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

	result = ft_strdup("");
	(*i)++;
	while (str[*i] && str[*i] != '"')
		result = process_dq_char(str, i, data, result);
	if (str[*i] == '"')
		(*i)++;
	return (result);
}

/*
** expand_chunk_m: expands one chunk from str at position *i.
** Returns the expanded string, wrapping quoted regions with \x01..\x02
** so the word splitter knows not to split on spaces inside them.
** Returns NULL for literal (unquoted) characters (caller appends str[*i]).
*/
static char	*expand_chunk_m(char *str, int *i, t_data *data)
{
	char	*r;
	char	*t;

	if (str[*i] == '\'')
	{
		r = ft_strdup("\x01");
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			r = append_char(r, str[(*i)++]);
		if (str[*i] == '\'')
			(*i)++;
		return (append_char(r, '\x02'));
	}
	if (str[*i] == '"')
	{
		t = expand_dq(str, i, data);
		r = append_str(ft_strdup("\x01"), t);
		free(t);
		return (append_char(r, '\x02'));
	}
	if (str[*i] == '$' && str[*i + 1]
		&& (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_'
			|| str[*i + 1] == '?' || str[*i + 1] == '{'))
		return (expand_dollar(str, i, data));
	return (NULL);
}

char	*expand_value(char *str, t_data *data)
{
	char	*result;
	char	*expanded;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		expanded = expand_chunk_m(str, &i, data);
		if (expanded)
		{
			result = append_str(result, expanded);
			free(expanded);
		}
		else
		{
			result = append_char(result, str[i]);
			i++;
		}
	}
	return (result);
}
