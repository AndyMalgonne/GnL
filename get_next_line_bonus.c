/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 08:48:45 by amalgonn          #+#    #+#             */
/*   Updated: 2023/12/12 10:50:51 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	read_error(int fd, char *buf)
{
	int	i;

	if (buf[0] != 0)
		return (1);
	i = read(fd, buf, BUFFER_SIZE);
	if (i > 0)
	{
		buf[i] = '\0';
		return (1);
	}
	return (0);
}

static char	*read_line_from_buffer(char *line, char *buf, int fd)
{
	int		i;

	i = 1;
	while (!(ft_strchr(line, '\n')) && i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		buf[i] = '\0';
		line = ft_strnjoin(line, buf, i);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buf[FD_MAX][BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int			i;

	if (fd >= FD_MAX || fd < 0 || read_error(fd, buf[fd]) == 0)
		return (NULL);
	line = ft_strdup(buf[fd]);
	line = read_line_from_buffer(line, buf[fd], fd);
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	newline = ft_strchr(line, '\n');
	if (newline != NULL)
	{
		i = newline - line + 1;
		ft_strlcpy(buf[fd], newline + 1, BUFFER_SIZE + 1);
	}
	else
	{
		i = ft_strlen(line);
		ft_strlcpy(buf[fd], "", BUFFER_SIZE + 1);
	}
	line[i] = '\0';
	return (line);
}
