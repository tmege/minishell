/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:10:53 by tmege             #+#    #+#             */
/*   Updated: 2025/05/12 14:14:33 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Ecrit une chaine de charactere suivie d'un saut de ligne dans un fichier*/

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
	}
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("usage : <string> <fd>\n");
		return (1);
	}

	char	*str;
	int	fd;
	str = argv[1];
	fd = atoi(argv[2]);
	if (fd < 0)
	{
		printf("invalid fd");
		return (1);
	}
	ft_putendl_fd(str, fd);
	return (0);
}
*/
