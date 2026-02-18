/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:12:35 by tmege             #+#    #+#             */
/*   Updated: 2025/05/12 14:36:08 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Permet d'ecrire n'importe quel nombre dans un fichier*/

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	ft_putchar_fd((nb % 10) + '0', fd);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("usage : <num> <fd>\n");
		return (1);
	}
	
	int	n;
	int	fd;
	n = atoi(argv[1]);
	fd = atoi(argv[2]);
	ft_putnbr_fd(n, fd);
	ft_putchar_fd('\n', fd);
	return (0);
}
*/
