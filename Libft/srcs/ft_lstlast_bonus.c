/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:47:52 by tmege             #+#    #+#             */
/*   Updated: 2025/05/17 15:48:00 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*retourne le dernier noeud de la liste*/

#include "libft.h"

/* retourne le dernier noeud de la liste 
 * verifie si la liste est nulle
 * sinon parcours jusqu'au next null
 */

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_list	*head;
	t_list	*last;
	t_list	*tmp;
	t_list	*node;
	int	i;

	head = NULL;
	i = 1;
	while (i < argc)
	{
		node = ft_lstnew(argv[i]);
		ft_lstadd_back(&head, node);
		i++;
	}
	last = ft_lstlast(head);
	if (last)
		printf("Last node : %s\n", (char *)last->content);
	else
		printf("The list is empty\n");
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	return (0);
}
*/
