/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir_file(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == redir_in)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == redir_out)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == redir_append)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == redir_heredoc)
		return (redir->fd);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file);
	}
	return (fd);
}

static int	redir_target(t_redir *redir)
{
	if (redir->type == redir_in || redir->type == redir_heredoc)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redirs;
	while (redir)
	{
		fd = open_redir_file(redir);
		if (fd < 0)
			return (-1);
		if (dup2(fd, redir_target(redir)) < 0)
		{
			close(fd);
			return (-1);
		}
		if (fd != redir_target(redir))
			close(fd);
		redir = redir->next;
	}
	return (0);
}
