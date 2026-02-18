/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:59:18 by tmege             #+#    #+#             */
/*   Updated: 2025/06/18 19:24:58 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_fdnode
{
	int					fd;
	char				*stash;
	struct s_fdnode		*next;
}	t_fdnode;

char		*get_next_line(int fd);
size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char *s1, char *s2);
t_fdnode	*get_fdnode(t_fdnode **head, int fd);
void		free_fdnode(t_fdnode **head, int fd);
char		*get_line(char *buffer);
char		*save_rest(char *buffer);
int			read_and_stash(t_fdnode *curr, int fd);

#endif
