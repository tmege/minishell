/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 00:00:00 by tmege             #+#    #+#             */
/*   Updated: 2026/02/21 00:00:00 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_dot(char **args)
{
	if (!args[1])
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		return (2);
	}
	ft_putstr_fd("minishell: .: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": not implemented\n", 2);
	return (1);
}
