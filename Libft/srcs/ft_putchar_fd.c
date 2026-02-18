/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:08:20 by tmege             #+#    #+#             */
/*   Updated: 2025/05/01 17:09:21 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* putchar qui permet d'ecrire sur un fichier*/

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	char	*c;
	int	i;

	if (argc != 2)
	{
		printf("usage : ./exec <arg1>");
		return (1);
	}
	c = argv[1];
	i = 0;
	while (c[i])
	{
		ft_putchar_fd(c[i], 1);
		i++;
	}
	return(0);
}
*/
