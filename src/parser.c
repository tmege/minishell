/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_type	token_to_redir(t_token_type type)
{
	if (type == token_redir_in)
		return (redir_in);
	if (type == token_redir_out)
		return (redir_out);
	if (type == token_heredoc)
		return (redir_heredoc);
	return (redir_append);
}

static int	is_redir_token(t_token_type type)
{
	return (type == token_redir_in || type == token_redir_out
		|| type == token_heredoc || type == token_append);
}

static void	free_arg_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

static t_token	*parse_one_cmd(t_token *cur, t_cmd *cmd)
{
	t_list	*args;

	args = NULL;
	while (cur && cur->type != token_pipe)
	{
		if (is_redir_token(cur->type))
		{
			redir_add_back(&cmd->redirs, redir_new(
					token_to_redir(cur->type),
					cur->next->value, cur->next->quoted));
			cur = cur->next->next;
		}
		else
		{
			ft_lstadd_back(&args, ft_lstnew(cur->value));
			cur = cur->next;
		}
	}
	cmd->args = list_to_args(args);
	free_arg_list(args);
	return (cur);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*cmd;
	t_cmd	*last;
	t_token	*cur;

	cmds = NULL;
	last = NULL;
	cur = tokens;
	while (cur)
	{
		cmd = cmd_new();
		cur = parse_one_cmd(cur, cmd);
		if (!cmds)
			cmds = cmd;
		else
			last->next = cmd;
		last = cmd;
		if (cur && cur->type == token_pipe)
			cur = cur->next;
	}
	return (cmds);
}
