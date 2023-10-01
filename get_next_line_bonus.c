/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 00:41:20 by kel-baam          #+#    #+#             */
/*   Updated: 2022/11/05 01:34:22 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*free_pointer(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static char	*read_from_file(int fd, char *str)
{
	int		nbyt;
	char	buff[BUFFER_SIZE + 1];
	char	*tmp;

	nbyt = 1;
	while (nbyt > 0)
	{
		if (ft_index_newline(str) >= 0)
			break ;
		nbyt = read(fd, buff, BUFFER_SIZE);
		if (nbyt == -1)
			return (free_pointer(&str));
		buff[nbyt] = 0;
		tmp = str;
		str = ft_strjoin(str, buff);
		free(tmp);
	}
	return (str);
}

static char	*check_fd(int fd, char *rest)
{
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!rest)
	{
		rest = ft_strdup("");
		if (!rest)
			return (NULL);
	}
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest[1024];
	char		*line;
	int			index;
	char		*tmp;

	rest[fd] = check_fd(fd, rest[fd]);
	if (!rest[fd])
		return (NULL);
	rest[fd] = read_from_file(fd, rest[fd]);
	if (!rest[fd] || !rest[fd][0])
		return (free_pointer(&rest[fd]));
	index = ft_index_newline(rest[fd]);
	if (index < 0)
	{
		line = rest[fd];
		rest[fd] = NULL;
	}
	else
	{
		tmp = rest[fd];
		line = ft_substr(rest[fd], 0, index + 1);
		rest[fd] = ft_strdup(&rest[fd][index + 1]);
		free(tmp);
	}
	return (line);
}
