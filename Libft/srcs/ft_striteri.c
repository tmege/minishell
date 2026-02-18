/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:23:50 by tmege             #+#    #+#             */
/*   Updated: 2025/05/15 12:06:53 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* applique une fonction f a chaque char 
 * 	d'une chaine s en lui passant l'index et
 * un pointeur vers ce char
 * verifie que s et f existent, si l'un est null, on ne fait rien
 * s'ils existent parcours chaque char et lui applique la fonction
 */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*

#include <stdio.h>

// test avec to_upper

void	to_upper(unsigned int i, char *c)
{
	(void)i;
	if (*c >= 'a' && *c <= 'z')
		*c = *c - 32;
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("usage : <string>\n");
		return (1);
	}
	
	char	*input;
	input = ft_strdup(argv[1]);
	if (!input)
	{
		printf("strdup error");
		return (1);
	}
	ft_striteri(input, to_upper);
	printf ("Result : %s\n", input);
	free(input);
	return (0);
}
*/
