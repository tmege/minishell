/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:00:35 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd_env_or_err(char *var, char *msg, t_data *data)
{
	char	*value;

	value = get_env_value(var, data);
	if (!value || value[0] == '\0')
	{
		free(value);
		ft_putstr_fd(msg, 2);
		return (NULL);
	}
	return (value);
}

static int	cd_update_dirs(char *oldpwd, t_data *data)
{
	char	cwd[1024];

	if (oldpwd)
		set_env_value("OLDPWD", oldpwd, data);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_value("PWD", cwd, data);
	return (0);
}

static char	*get_cd_target(char **args, t_data *data)
{
	char	*target;

	if (!args[1])
		return (cd_env_or_err("HOME",
				"minishell: cd: HOME not set\n", data));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		target = cd_env_or_err("OLDPWD",
				"minishell: cd: OLDPWD not set\n", data);
		if (target)
		{
			ft_putstr_fd(target, 1);
			ft_putstr_fd("\n", 1);
		}
		return (target);
	}
	return (ft_strdup(args[1]));
}

int	builtin_cd(char **args, t_data *data)
{
	char	*target;
	char	oldpwd[1024];
	char	*old_ptr;

	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	old_ptr = getcwd(oldpwd, sizeof(oldpwd));
	target = get_cd_target(args, data);
	if (!target)
		return (1);
	if (chdir(target) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(target);
		free(target);
		return (1);
	}
	free(target);
	return (cd_update_dirs(old_ptr, data));
}
