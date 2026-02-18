/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:57:43 by tmege             #+#    #+#             */
/*   Updated: 2025/05/12 13:58:42 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 	remplir un bloc de memoire avec une valeur donnee
*	conversion s en unsigned char pour travailler byte par byte
*	remplir n premier bytes du bloc memoire ptr byte par byte
*	retour pointeur initial
*/

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("Usage : <str> <char> <n>\n");
		return (1);
	}
	
	int	c;
	size_t	n;
	size_t	len;
	char	*str;
	c = (unsigned char)argv[2][0];
	n = atoi(argv[3]);
	str = ft_strdup(argv[1]);
	len = ft_strlen(str);
	if (n > len)
	{
		printf("n > len, trim to fit\n");
		n = len;
	}
	printf("str before memset : \"%s\"\n", str);
	ft_memset(str, c, n);
	printf("str after memset : \"%s\"\n", str);
	free(str);
	return (0);
}
*/
