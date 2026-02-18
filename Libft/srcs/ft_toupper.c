/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:03:06 by tmege             #+#    #+#             */
/*   Updated: 2025/04/30 16:05:31 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* lower to MAJ char by char */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	i;
	char	*str;

	if (argc != 2)
	{
		printf("usage : ./exec <c>\n");
		return (1);
	}
	i = 0;
	str = argv[1];
	printf("Og string : %s", str);
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	printf("New string : %s", str);
	return (0);
}
*/
