/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:09:34 by tmege             #+#    #+#             */
/*   Updated: 2025/05/12 14:39:05 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Permet d'ecrire une string dans un fichier*/

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Usage: <str> <fd>\n");
		return (1);
	}

	char *str = argv[1];
	int fd = atoi(argv[2]);

	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);

	return (0);
}
*/
