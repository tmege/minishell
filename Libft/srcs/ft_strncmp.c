/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:45:37 by tmege             #+#    #+#             */
/*   Updated: 2025/05/15 11:53:18 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* comparer les n premiers caracteres de s1 et s2
 * on boucle jusqu'a avoir comparer n caracteres
 * si les char i sont diff on retour la diff en unsigned char entre les deux
 * si on rencontre le char nul en s1[i] alors elles sont egales on retourne 0
 * si la boucle fini alors on a trouve aucune difference en n char on retourne 0
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("usage : ./exec <s1> <s2> <sizen>\n");
		return (1);
	}
	
	const char	*s1;
	const char	*s2;
	size_t		n;
	int		result;

	s1 = argv[1];
	s2 = argv[2];
	n = atoi(argv[3]);
	result = ft_strncmp(s1, s2, n);
	printf("Result ft_strncmp('%s' ; '%s' , %zu) = %d\n", s1, s2, n, result);
	return (0);
}
*/
