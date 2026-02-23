/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/23 00:00:00 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static t_token	*make_word_tokens(char *value)
{
	t_token	*head;
	char	*word;
	int		i;
	int		start;

	head = NULL;
	i = 0;
	while (value[i])
	{
		while (value[i] && is_ifs(value[i]))
			i++;
		if (!value[i])
			break ;
		start = i;
		while (value[i] && !is_ifs(value[i]))
			i++;
		word = ft_substr(value, start, i - start);
		token_add_back(&head, token_new(word, token_word, 0));
	}
	return (head);
}

static t_token	*do_word_split(t_token **tokens, t_token *prev,
	t_token *cur, t_token *next)
{
	t_token	*split;
	t_token	*last;

	split = make_word_tokens(cur->value);
	free(cur->value);
	free(cur);
	if (!split)
	{
		if (prev)
			prev->next = next;
		else
			*tokens = next;
		return (prev);
	}
	last = split;
	while (last->next)
		last = last->next;
	last->next = next;
	if (prev)
		prev->next = split;
	else
		*tokens = split;
	return (last);
}

void	expand_tokens(t_token **tokens, t_data *data)
{
	t_token	*cur;
	t_token	*prev;
	t_token	*next;
	char	*expanded;

	prev = NULL;
	cur = *tokens;
	while (cur)
	{
		next = cur->next;
		if (cur->type == token_word)
		{
			expanded = expand_value(cur->value, data, cur->quoted);
			free(cur->value);
			cur->value = expanded;
			if (!cur->quoted)
			{
				prev = do_word_split(tokens, prev, cur, next);
				cur = next;
				continue ;
			}
		}
		prev = cur;
		cur = cur->next;
	}
}
