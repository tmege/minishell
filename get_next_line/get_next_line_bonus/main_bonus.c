/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmege <tmege@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:45:41 by tmege             #+#    #+#             */
/*   Updated: 2026/02/16 00:00:00 by tmege            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

static void	read_file(char *filename)
{
	int		fd;
	char	*line;

	printf("----- Reading file: %s -----\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return ;
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <file1> [file2 ...]\n", argv[0]);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		read_file(argv[i]);
		i++;
	}
	return (0);
}
