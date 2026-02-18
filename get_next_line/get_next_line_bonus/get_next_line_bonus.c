/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:45:41 by tmege             #+#    #+#             */
/*   Updated: 2025/06/18 19:25:35 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer || !*buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*save_rest(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(ft_strlen(buffer) - i + 1);
	if (!new_buffer)
		return (NULL);
	i++;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

int	read_and_stash(t_fdnode *curr, int fd)
{
	char	tmp[BUFFER_SIZE + 1];
	int		bytes;

	bytes = 1;
	while (!ft_strchr(curr->stash, '\n') && bytes != 0)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes < 0)
			return (-1);
		tmp[bytes] = '\0';
		curr->stash = ft_strjoin(curr->stash, tmp);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_fdnode	*fdlist;
	t_fdnode		*curr;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	curr = get_fdnode(&fdlist, fd);
	if (!curr || read_and_stash(curr, fd) == -1)
	{
		free_fdnode(&fdlist, fd);
		return (NULL);
	}
	line = get_line(curr->stash);
	curr->stash = save_rest(curr->stash);
	if (!line)
		free_fdnode(&fdlist, fd);
	return (line);
}
