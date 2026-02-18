/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:30:57 by tmege             #+#    #+#             */
/*   Updated: 2025/04/30 12:31:43 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* est ce un Ascii*/

int	ft_isascii(int n)
{
	if (n >= 0 && n <= 127)
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
	if (ft_isascii(n) == 1)
		printf("%c is ascii.\n", n);
	else
		printf("%c is not ascii.\n", n);
	return (0);
}
*/
