/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:28:07 by tmege             #+#    #+#             */
/*   Updated: 2025/04/30 12:29:24 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Est ce un chiffre */

int	ft_isdigit(int n)
{
	if (n >= '0' && n <= '9')
		return (1);
	return (0);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int n;

	if (argc != 2)
	{
		printf("usage : ./exec <n>\n");
		return (1);
	}
	n = argv[1][0];
	if (ft_isdigit(n) == 1)
		printf("%c is digit.\n", n);
	else
		printf("%c is not digit.\n", n);
	return (0);
}
*/
