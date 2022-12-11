/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:42:55 by oaboulgh          #+#    #+#             */
/*   Updated: 2022/11/21 02:59:58 by oaboulgh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*arr;
	const unsigned char	*source;
	size_t				i;

	source = src;
	arr = dst;
	i = 0;
	if (dst == src)
		return (dst);
	while (i < n)
	{
		arr[i] = source[i];
		i++;
	}
	return (dst);
}

static char	*get_line(char *s)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!ft_strchr(s, '\n'))
		return (ft_strdup(s));
	while (s[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	ft_strlcpy(line, s, i + 2);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static char	*read_file(int fd, char *save)
{
	int		buf_count;
	char	*buffer;
	char	*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	buf_count = 1;
	while (buf_count > 0)
	{
		buf_count = read (fd, buffer, BUFFER_SIZE);
		if (buf_count == -1)
			return (free(buffer), NULL);
		buffer[buf_count] = '\0';
		if (!save)
			save = ft_strdup("");
		tmp = save;
		save = ft_strjoin(save, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (save);
}

static char	*save_rest(char *s)
{
	int		i;
	char	*rest_line;

	i = 0;
	if (!ft_strchr(s, '\n'))
		return (free(s), NULL);
	while (s[i] != '\n')
		i++;
	rest_line = ft_strdup (&s[i + 1]);
	free (s);
	return (rest_line);
}

char	*get_next_line(int fd)
{
	static char	*head[10240];
	char		*buffer;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 10240)
		return (NULL);
	buffer = NULL;
	head[fd] = read_file(fd, head[fd]);
	if (!head[fd])
		return (NULL);
	buffer = get_line(head[fd]);
	head[fd] = save_rest(head[fd]);
	if (buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (buffer);
}
