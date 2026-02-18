/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:48:08 by tmege             #+#    #+#             */
/*   Updated: 2025/05/17 15:48:29 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*supprime tous les elements de la linklist 1 par 1 
  dans la boucle via lstdelone*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}
/*
#include <stdio.h>

void	del_content(void *content)
{
	free(content);
}

int	main(int argc, char *argv[])
{
	t_list	*head;
	t_list	*node;
	t_list	*tmp;
	int	i;

	head = NULL;
	i = 1;
	while (i < argc)
	{
		node = ft_lstnew(ft_strdup(argv[i]));
		ft_lstadd_back(&head, node);
		i++;
	}
	printf("List :\n");
	tmp = head;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&head, del_content);
	if (!head)
		printf("New list :\nEmpty and set to NULL\n");
	return (0);
}
*/
