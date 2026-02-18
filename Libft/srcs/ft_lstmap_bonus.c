/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:49:09 by tmege             #+#    #+#             */
/*   Updated: 2025/05/17 15:49:30 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* cree une nouvelle liste issue de lst et appliquant 
  la fonction f a chaque element*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	new_list = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/*
#include <stdio.h>

void	del_content(void *content)
{
	free(content);
}

void	*to_upper(void *content)
{
	char	*str;
	char	*upper;
	int	i;

	str = (char *)content;
	upper = ft_strdup(str);
	if (!upper)
		return (NULL);
	i = 0;
	while (upper[i])
	{
		upper[i] = ft_toupper(upper[i]);
		i++;
	}
	return (upper);
}


int	main(int argc, char*argv[])
{
	t_list	*head;
	t_list	*node;
	t_list	*mapped;
	int	i;

	i = 1;
	head = NULL;
	while (i < argc)
	{
		node = ft_lstnew(ft_strdup(argv[i]));
		if (!node)
		{
			ft_lstclear(&head, del_content);
			return (1);
		}
		ft_lstadd_back(&head, node);
		i++;
	}
	mapped = ft_lstmap(head, to_upper, del_content);
	printf("Mapped list :\n");
	while (mapped)
	{
		printf("%s\n", (char *)mapped->content);
		mapped = mapped->next;
	}
	ft_lstclear(&head, del_content);
	ft_lstclear(&mapped, del_content);
	return (0);
}
*/
