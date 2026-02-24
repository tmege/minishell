/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:00:00 by tmege             #+#    #+#             */
/*   Updated: 2026/02/24 00:00:00 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_open_quote(int start)
{
	char	in_quote;
	int		quote_pos;
	int		i;

	in_quote = 0;
	quote_pos = -1;
	i = 0;
	while (i < start)
	{
		if (!in_quote && (rl_line_buffer[i] == '\''
				|| rl_line_buffer[i] == '"'))
		{
			in_quote = rl_line_buffer[i];
			quote_pos = i;
		}
		else if (in_quote && rl_line_buffer[i] == in_quote)
		{
			in_quote = 0;
			quote_pos = -1;
		}
		i++;
	}
	if (in_quote)
		return (quote_pos);
	return (-1);
}

static int	has_space_in_quote(int quote_pos, int start)
{
	int	i;

	i = quote_pos + 1;
	while (i < start)
	{
		if (rl_line_buffer[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

static char	**minishell_completion(const char *text, int start, int end)
{
	int	quote_pos;

	(void)end;
	rl_attempted_completion_over = 1;
	if (*rl_line_buffer == '\0' || (start == 0 && *text == '\0'))
		return (NULL);
	quote_pos = find_open_quote(start);
	if (quote_pos >= 0 && has_space_in_quote(quote_pos, start))
		return (NULL);
	return (rl_completion_matches(text, rl_filename_completion_function));
}

void	setup_completion(void)
{
	rl_attempted_completion_function = minishell_completion;
}
