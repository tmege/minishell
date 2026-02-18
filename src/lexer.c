/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_unclosed_quote(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (!line[i])
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}

static t_token	*read_operator(char *line, int *i)
{
	if (line[*i] == '|')
	{
		(*i)++;
		return (token_new(ft_strdup("|"), token_pipe, 0));
	}
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		*i += 2;
		return (token_new(ft_strdup("<<"), token_heredoc, 0));
	}
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		*i += 2;
		return (token_new(ft_strdup(">>"), token_append, 0));
	}
	if (line[*i] == '<')
	{
		(*i)++;
		return (token_new(ft_strdup("<"), token_redir_in, 0));
	}
	(*i)++;
	return (token_new(ft_strdup(">"), token_redir_out, 0));
}

static t_token	*read_word(char *line, int *i)
{
	int		start;
	int		quoted;
	char	*val;

	start = *i;
	quoted = 0;
	while (line[*i] && !is_metachar(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			quoted = 1;
			*i = skip_quotes(line, *i);
		}
		else
			(*i)++;
	}
	val = ft_substr(line, start, *i - start);
	return (token_new(val, token_word, quoted));
}

static void	tokenize_char(t_token **tokens, char *line, int *i)
{
	t_token	*tok;

	if (line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
		tok = read_operator(line, i);
	else
		tok = read_word(line, i);
	token_add_back(tokens, tok);
}

t_token	*tokenize(char *line, int *err)
{
	t_token	*tokens;
	int		i;

	*err = 0;
	if (has_unclosed_quote(line))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		*err = 1;
		return (NULL);
	}
	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else
			tokenize_char(&tokens, line, &i);
	}
	return (tokens);
}
