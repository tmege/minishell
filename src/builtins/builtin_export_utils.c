/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env(char **sorted, int count)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < count - 1)
	{
		j = i;
		while (++j < count)
		{
			if (ft_strncmp(sorted[i], sorted[j],
					ft_strlen(sorted[j]) + 1) > 0)
			{
				tmp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = tmp;
			}
		}
	}
}

char	**copy_sort_env(char **envp, int count)
{
	char	**sorted;
	int		i;

	sorted = malloc(sizeof(char *) * count);
	if (!sorted)
		return (NULL);
	i = -1;
	while (++i < count)
		sorted[i] = envp[i];
	sort_env(sorted, count);
	return (sorted);
}
