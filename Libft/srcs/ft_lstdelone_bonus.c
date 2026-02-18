/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:49:43 by tmege             #+#    #+#             */
/*   Updated: 2025/05/17 15:49:46 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*
#include <stdio.h>

void	del_content(void *content)
{
	free(content);
}

int	main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("usage : ./exec <index> <str1> <str2>...\n");
		return (1);
	}

	int	target;
	int	index;
	t_list	*head;
	t_list	*node;
	t_list	*tmp;
	t_list	*prev;
	t_list	*delete;
	int	i;

	head = NULL;
	i = 2;
	while (i < argc)
	{
		node = ft_lstnew(ft_strdup(argv[i]));
		ft_lstadd_back(&head, node);
		i++;
	}
	target = atoi(argv[1]);
	if (target == 0 && head)
	{
		tmp = head;
		head = head->next;
		ft_lstdelone(tmp, del_content);
	}
	else
	{
		prev = head;
		index = 1;

		while (prev && prev->next && index < target)
		{
			prev = prev->next;
			index++;
		}
		if (prev && prev->next && index == target)
		{
			delete = prev->next;
			prev->next = delete->next;
			ft_lstdelone(delete, del_content);
		}
	}
	tmp = head;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	while (head)
	{
		tmp = head;
		head = head->next;
		del_content(tmp->content);
		free(tmp);
	}
	return (0);
}
*/
