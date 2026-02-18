/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:58:26 by tmege             #+#    #+#             */
/*   Updated: 2025/05/15 18:41:59 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ajoute un element au debut de la linklist*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_list	*head;
	t_list	*current;
	t_list	*tmp;
	int		i;

	head = NULL;
	i = 1;

	if (argc < 2)
	{
		printf("usage : ./exec <str1> <str2> ...\n");
		return (1);
	}
	while (i < argc)
	{
		t_list *new_node = ft_lstnew((void *)argv[i]);
		if (!new_node)
		{
			printf("Memory alloc error");
			return (1);
		}
		ft_lstadd_front(&head, new_node);
		i++;
	}
	printf("list insight : (reverse order from entry)\n");
	current = head;
	while (current)
	{
		printf("- %s\n", (char *)current->content);
		current = current->next;
	}
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	return (0);
}
*/
