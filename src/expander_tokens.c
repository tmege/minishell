/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/28 00:00:00 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** collect_word: collects one word from value starting at *i.
** Tracks quoted regions via \x01 (open) and \x02 (close) markers.
** Inside a quoted region, IFS chars are NOT word separators.
** \x01/\x02 markers are consumed and stripped from the word.
** Sets *q to 1 if any quoted marker was encountered (for redir->quoted).
*/
static char	*collect_word(char *value, int *i, int *q)
{
	char	*word;
	int		in_q;

	word = NULL;
	in_q = 0;
	*q = 0;
	while (value[*i] && (in_q || value[*i] == '\x01'
			|| (value[*i] != ' ' && value[*i] != '\t'
				&& value[*i] != '\n')))
	{
		if (value[*i] == '\x01')
		{
			in_q = 1;
			*q = 1;
		}
		else if (value[*i] == '\x02')
			in_q = 0;
		else
			word = append_char(word, value[*i]);
		(*i)++;
	}
	if (!word)
		return (ft_strdup(""));
	return (word);
}

/*
** make_word_tokens: splits value into tokens using IFS word splitting.
** Only splits on unquoted IFS chars (outside \x01..\x02 regions).
** Strips \x01/\x02 markers from resulting word values.
*/
static t_token	*make_word_tokens(char *value)
{
	t_token	*head;
	char	*word;
	int		i;
	int		q;

	head = NULL;
	i = 0;
	while (value[i])
	{
		while (value[i] && value[i] != '\x01'
			&& (value[i] == ' ' || value[i] == '\t' || value[i] == '\n'))
			i++;
		if (!value[i])
			break ;
		word = collect_word(value, &i, &q);
		token_add_back(&head, token_new(word, token_word, q));
	}
	return (head);
}

/*
** update_word_token: updates cur->value in place.
** If data is non-NULL: expands variables (normal word token).
** If data is NULL:    strips quotes only (heredoc delimiter token).
*/
static void	update_word_token(t_token *cur, t_data *data)
{
	char	*val;

	if (data)
		val = expand_value(cur->value, data);
	else
		val = strip_quotes_only(cur->value, &cur->quoted);
	free(cur->value);
	cur->value = val;
}

static t_token	*do_word_split(t_token **tokens, t_token *prev, t_token *cur)
{
	t_token	*split;
	t_token	*last;
	t_token	*next;

	next = cur->next;
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

	prev = NULL;
	cur = *tokens;
	while (cur)
	{
		if (cur->type == token_word && !(prev && prev->type == token_heredoc))
		{
			update_word_token(cur, data);
			prev = do_word_split(tokens, prev, cur);
			if (prev)
				cur = prev->next;
			else
				cur = *tokens;
			continue ;
		}
		if (cur->type == token_word)
			update_word_token(cur, NULL);
		prev = cur;
		cur = cur->next;
	}
}
