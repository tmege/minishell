/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_entry(char *entry)
{
	char	*eq;

	eq = ft_strchr(entry, '=');
	if (eq)
	{
		write(1, "declare -x ", 11);
		write(1, entry, eq - entry);
		write(1, "=\"", 2);
		ft_putstr_fd(eq + 1, 1);
		write(1, "\"\n", 2);
	}
	else
		ft_printf("declare -x %s\n", entry);
}

static void	print_sorted_env(t_data *data)
{
	int		count;
	int		i;
	char	**sorted;

	count = 0;
	while (data->envp[count])
		count++;
	sorted = copy_sort_env(data->envp, count);
	if (!sorted)
		return ;
	i = -1;
	while (++i < count)
		print_export_entry(sorted[i]);
	free(sorted);
}

static int	is_valid_export_id(char *arg)
{
	int	i;

	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_one(char *arg, t_data *data)
{
	char	*eq;
	char	*name;

	if (!is_valid_export_id(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		add_env_no_value(arg, data);
		return (0);
	}
	name = ft_substr(arg, 0, eq - arg);
	set_env_value(name, eq + 1, data);
	free(name);
	return (0);
}

int	builtin_export(char **args, t_data *data)
{
	int	i;
	int	ret;

	if (!args[1])
	{
		print_sorted_env(data);
		return (0);
	}
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (export_one(args[i], data) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
