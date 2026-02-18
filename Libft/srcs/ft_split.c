/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:24:07 by tmege             #+#    #+#             */
/*   Updated: 2025/05/15 12:21:50 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* compteur de mots
 * retourne null si chaine est vide
 * incremente si c nest pas le caractere separateurs
 * parcours la chaine jusqua un caractere different
 * de C et incremente le compteur
 * retourne le compte des mots
 */

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c && (i == 0 || (s[i - 1] == c)))
			count++;
		i++;
	}
	return (count);
}

/* trouve la len du prochain mot
 * compteur i jusqu'a rencontre le separateur ou fin de chaine
 * retourne len du mot suivant
 */

static size_t	ft_next_word_len(char const *s, size_t i, char c)
{
	size_t	count;

	count = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

/* liberer la memoire dans tab jusqua index
 * libere la memoire allouee via malloc
 */

static void	ft_free_tab(char **tab, size_t index)
{
	while (index--)
		free(tab[index]);
	free(tab);
}

/* creer un tab de chaines de mot separes selon le char
 * alloction de tab en utilisant wordcount 
 * 	pour savoir combien de mot + caractere null
 * boucle pour extraire chaque mot, saut des separateurs
 * 	 et on recupere la len du mot suivant
 * on extrait le mot avec ft_substr qui copi s de length end a partir de i
 * si le ft_substr echoue on libere l'espace allouee avec ft_free_tab
 * on avance i de la longueur du mot et on passe 
 * 	au suivant dans la prochaine case de tab
 * on retourne tab qui contient tous les mots extraits
 */

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	tab_index;
	size_t	end;
	char	**tab;

	tab = ft_calloc(ft_wordcount(s, c) + 1, sizeof(char *));
	if (!tab || !s)
		return (NULL);
	i = 0;
	tab_index = 0;
	while (tab_index < ft_wordcount(s, c))
	{
		while (s[i] == c)
			i++;
		end = ft_next_word_len(s, i, c);
		tab[tab_index] = ft_substr(s, i, end);
		if (!tab[tab_index])
		{
			ft_free_tab(tab, tab_index);
			return (NULL);
		}
		i += end;
		tab_index++;
	}
	return (tab);
}
/*
#include <stdio.h>

int	main()
{
	char const *s = "iker casillas le goat";
	char c = ' ';
	int i = 0;
	char **res = ft_split(s, c);
	while (res[i])
	{
		printf("%d : %s\n", i, res[i]);
		free(res[i]);
		i++;
	}
	free(res);
	return (0);
}

#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("usage : <str> <char>\n");
		return (1);
	}
	int	i;
	char	**result;
	result = ft_split(argv[1], argv[2][0]);
	i = 0;
	if (!result)
	{
		printf("split failed\n");
		return (1);
	}
	if (argv[2][0] == '\0')
	{
		printf("error: empty delimiter\n");
		return (1);
	}

	while (result[i])
	{
		printf("[%d] \"%s\"\n", i, result[i]);
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}
*/
