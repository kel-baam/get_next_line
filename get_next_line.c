/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:46:12 by kel-baam          #+#    #+#             */
/*   Updated: 2022/11/04 10:46:15 by kel-baam         ###   ########.fr       */
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
	static char	*rest;
	char		*line;
	int			index;
	char		*tmp;

	rest = check_fd(fd, rest);
	if (!rest)
		return (NULL);
	rest = read_from_file(fd, rest);
	if (!rest || !rest[0])
		return (free_pointer(&rest));
	index = ft_index_newline(rest);
	if (index < 0)
	{
		line = rest;
		rest = NULL;
	}
	else
	{
		tmp = rest;
		line = ft_substr(rest, 0, index + 1);
		rest = ft_strdup(&rest[index + 1]);
		free(tmp);
	}
	return (line);
}
