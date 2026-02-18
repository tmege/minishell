/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_overflow(long long n, int digit, int sign)
{
	if (sign == 1 && n > (9223372036854775807LL - digit) / 10)
		return (1);
	if (sign == -1
		&& n > (9223372036854775807LL - digit + 1) / 10)
		if (!(n == 922337203685477580LL && digit <= 8))
			return (1);
	return (0);
}

static int	ft_atoll_safe(char *str, long long *result)
{
	int			i;
	int			sign;
	long long	n;

	i = 0;
	sign = 1;
	n = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (check_overflow(n, str[i] - '0', sign))
			return (0);
		n = n * 10 + (str[i] - '0');
		i++;
	}
	*result = n * sign;
	return (1);
}

static void	exit_numeric_error(char *arg, t_data *data)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	data->running = 0;
	data->exit_status = 2;
}

int	builtin_exit(char **args, t_data *data)
{
	long long	code;

	if (!data->in_pipe)
		ft_putstr_fd("exit\n", 2);
	if (!args[1])
	{
		data->running = 0;
		return (data->exit_status);
	}
	if (!is_numeric(args[1]) || !ft_atoll_safe(args[1], &code))
	{
		exit_numeric_error(args[1], data);
		return (2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	data->running = 0;
	return ((unsigned char)code);
}
