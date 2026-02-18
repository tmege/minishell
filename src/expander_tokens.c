/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_token(t_token **tokens, t_token *prev, t_token *cur)
{
	if (prev)
		prev->next = cur->next;
	else
		*tokens = cur->next;
	free(cur->value);
	free(cur);
}

static int	try_remove(t_token **tokens, t_token **prev, t_token **cur)
{
	if (!(*cur)->quoted && (*cur)->value[0] == '\0')
	{
		remove_token(tokens, *prev, *cur);
		if (*prev)
			*cur = (*prev)->next;
		else
			*cur = *tokens;
		return (1);
	}
	return (0);
}

void	expand_tokens(t_token **tokens, t_data *data)
{
	t_token	*cur;
	t_token	*prev;
	char	*expanded;

	prev = NULL;
	cur = *tokens;
	while (cur)
	{
		if (cur->type == token_word)
		{
			expanded = expand_value(cur->value, data, cur->quoted);
			free(cur->value);
			cur->value = expanded;
			if (try_remove(tokens, &prev, &cur))
				continue ;
		}
		prev = cur;
		cur = cur->next;
	}
}
