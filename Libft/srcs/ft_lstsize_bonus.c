/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:33:15 by tmege             #+#    #+#             */
/*   Updated: 2025/05/15 18:40:52 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_list	*head;
	int		i;
	int		size;
	t_list	*tmp;

	head = NULL;
	i = 1;
	while (i < argc)
	{
		t_list *node = ft_lstnew(argv[i]);
		ft_lstadd_front(&head, node);
		i++;
	}
	size = ft_lstsize(head);
	printf("Nodes numbers in the list : %d\n", size);
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	return (0);
} 
*/
