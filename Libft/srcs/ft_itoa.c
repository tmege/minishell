/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:30:46 by tmege             #+#    #+#             */
/*   Updated: 2025/05/12 12:25:24 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* converti un int en une chaine de characteres
 * conversion n en long pour eviter overflow avec entier negatif
 * calcul de la len pour savoir le nbr de chiffres a copier
 * allocation memoire len+1
 * caractere nul mis en fin de chaine
 * gestion des nbr negatifs
 * gestion cas du nb = 0
 * conversion de l'entier en chaine char en commencant a remplir par la fin
 * retourne la chaine
 */

#include "libft.h"

static int	count_digits(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	nb;

	nb = (long)n;
	len = count_digits(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("usage : ./exec <argv1> <argv2> .. ");
		return (1);
	}

	int	i;
	int	value;
	char	*result;

	i = 1;
	while (i < argc)
	{
		value = ft_atoi(argv[i]);
		result = ft_itoa(value);
		if (result)
		{
			printf("ft_itoa(%d) = \"%s\"\n", value, result);
			free(result);
		}
		else
			printf("ft_itoa(%d) = NULL (malloc failed)\n", value);
		i++;
	}
	return (0);
}
*/
