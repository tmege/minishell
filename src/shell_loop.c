/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_line(t_data *data, char *line)
{
	t_token	*tokens;
	int		err;

	tokens = tokenize(line, &err);
	if (!tokens)
	{
		if (err)
			data->exit_status = 2;
		return ;
	}
	if (!check_syntax(tokens))
	{
		data->exit_status = 2;
		free_tokens(tokens);
		return ;
	}
	expand_tokens(&tokens, data);
	data->cmds = parse_tokens(tokens);
	free_tokens(tokens);
	execute_cmds(data);
	free_cmds(data->cmds);
	data->cmds = NULL;
}

static char	*build_prompt(t_data *data)
{
	char	*user;
	char	*prompt;

	user = get_env_value("USER", data);
	if (!user || user[0] == '\0')
	{
		free(user);
		return (ft_strdup("minishell> "));
	}
	prompt = ft_strjoin(user, "@minishell> ");
	free(user);
	return (prompt);
}

static void	handle_line(t_data *data, char *line)
{
	if (line[0] != '\0')
	{
		add_history(line);
		process_line(data, line);
	}
	free(line);
}

void	shell_loop(t_data *data)
{
	char	*line;
	char	*prompt;

	while (data->running)
	{
		setup_signals();
		prompt = build_prompt(data);
		line = readline(prompt);
		free(prompt);
		if (g_status)
		{
			data->exit_status = 130;
			g_status = 0;
		}
		if (!line)
		{
			printf("exit\n");
			data->running = 0;
			break ;
		}
		handle_line(data, line);
	}
}
