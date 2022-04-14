/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:11:32 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/28 13:09:30 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "libftprintf.h"

void	*ft_get_end(char *memory)
{
	if (*memory == 0)
		return (memory);
	while (*memory && *memory != '\n')
		memory++;
	if (*memory == '\n')
		return (++memory);
	return (memory);
}

void	*ft_getline(char *memory)
{
	int		i;
	char	*line;

	i = 0;
	line = malloc(sizeof(*line) * ft_strlen_nl(memory) + 1);
	if (line == 0)
		return (0);
	while (memory[i] != '\n' && memory[i] != '\0')
	{
		line[i] = memory[i];
		i++;
	}
	line[i] = memory[i];
	if (line[i] == '\n')
	{
		i++;
		line[i] = 0;
	}
	ft_strcpy(memory, ft_get_end(memory));
	return (line);
}

char	*ft_make_magic(int fd, char buffer[BUFFER_SIZE + 1], int bytes_read)
{
	static char	*memory;

	if (fd == GNL_FLUSH)
	{
		free(memory);
		memory = NULL;
		return (0);
	}
	if (memory == 0)
		memory = ft_strdup("");
	while (bytes_read > 0 && ft_strchr(memory, '\n') == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if ((bytes_read == -1 || (bytes_read == 0 && *memory == 0)))
		{
			free(memory);
			memory = NULL;
			return (0);
		}
		buffer[bytes_read] = 0;
		memory = ft_strjoin_free(memory, buffer);
	}
	return (ft_getline(memory));
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	if (fd == GNL_FLUSH)
		ft_make_magic(fd, buffer, 0);
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (0);
	bytes_read = 1;
	line = ft_make_magic(fd, buffer, bytes_read);
	if (line && *line == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
