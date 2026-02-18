/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(t_token_type type)
{
	return (type == token_redir_in || type == token_redir_out
		|| type == token_heredoc || type == token_append);
}

static int	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

int	check_syntax(t_token *tokens)
{
	t_token	*cur;

	if (!tokens)
		return (1);
	if (tokens->type == token_pipe)
		return (syntax_error("|"));
	cur = tokens;
	while (cur)
	{
		if (cur->type == token_pipe)
		{
			if (!cur->next || cur->next->type == token_pipe)
				return (syntax_error("|"));
		}
		if (is_redir(cur->type))
		{
			if (!cur->next || cur->next->type != token_word)
				return (syntax_error(cur->value));
		}
		cur = cur->next;
	}
	return (1);
}
