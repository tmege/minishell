/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:31:16 by tmege             #+#    #+#             */
/*   Updated: 2025/05/17 15:47:45 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*cree un nouveau noeud avec un contenu donne et le next 
  initialise a NULL, pas lier dans la liste
  utiliser par exemple lst addback pour mettre ce noeud a la fin*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("usage : <noeud>");
		return (1);
	}
	t_list *node;
	node = ft_lstnew((void *)argv[1]);
	if (!node)
	{
		printf("memory alloc error");
		return (1);
	}
	printf("Node : %s\n", (char *)node->content);
	free(node);
	return (0);
}
*/
