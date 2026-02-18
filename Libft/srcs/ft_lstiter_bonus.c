/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:48:47 by tmege             #+#    #+#             */
/*   Updated: 2025/05/17 15:48:52 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*applique fonction f a chaque element de la linklist sur la liste d'origine*/

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>

void	del_content(void *content)
{
	free(content);
}

void	print_upper(void *content)
{
	if (!content)
		return ;

	char	*str;

	str = (char *)content;
	while (*str)
	{
		ft_putchar_fd(ft_toupper(*str), 1);
		str++;
	}
	ft_putchar_fd('\n', 1);
}

int	main(int argc, char *argv[])
{
	t_list	*head;
	t_list	*node;
	t_list	*tmp;
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
	printf("List upper :\n");
	ft_lstiter(head, print_upper);
	ft_lstclear(&head, del_content);
	return (0);
}
*/
