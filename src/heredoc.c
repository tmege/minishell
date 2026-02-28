/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sigint(int sig)
{
	(void)sig;
	g_status = 130;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

static void	setup_signals_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_sigint;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

static void	write_heredoc_line(int fd, char *line, int quoted, t_data *data)
{
	char	*expanded;
	int		i;

	if (!quoted)
	{
		expanded = expand_value(line, data);
		i = 0;
		while (expanded[i])
		{
			if (expanded[i] != '\x01' && expanded[i] != '\x02')
				write(fd, &expanded[i], 1);
			i++;
		}
		free(expanded);
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static void	read_heredoc_lines(int *pfd, char *delim, int q, t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delim,
				ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(pfd[1], line, q, data);
		free(line);
	}
	close(pfd[1]);
}

int	handle_heredoc(char *delim, int quoted, t_data *data)
{
	int		pipefd[2];
	int		stdin_copy;

	if (pipe(pipefd) < 0)
		return (-1);
	stdin_copy = dup(STDIN_FILENO);
	setup_signals_heredoc();
	read_heredoc_lines(pipefd, delim, quoted, data);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
	if (g_status == 130)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (pipefd[0]);
}
