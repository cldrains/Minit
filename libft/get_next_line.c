/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:30:03 by tevers            #+#    #+#             */
/*   Updated: 2023/02/23 04:32:29 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_next(char *buf)
{
	size_t	i;
	size_t	j;
	char	*rest;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		++i;
	if (!buf[i])
		return (free(buf), NULL);
	rest = ft_calloc((ft_strlen(buf) - i + 1), sizeof(char));
	if (!rest)
		return (free(buf), NULL);
	j = 0;
	while (buf[++i])
		rest[j++] = buf[i];
	return (free(buf), rest);
}

char	*ft_line(char *buf)
{
	size_t	i;
	char	*ret;

	i = 0;
	if (!buf[i])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	ret = ft_calloc(i + 2, sizeof(char));
	if (!ret)
		return (free(buf), NULL);
	i = -1;
	while (buf[++i] && buf[i] != '\n')
		ret[i] = buf[i];
	if (buf[i] == '\n')
		ret[i++] = '\n';
	ret[i] = '\0';
	return (ret);
}

char	*ft_readsave(int fd, char *left_str)
{
	char	*buf;
	int		bytes_read;

	if (!left_str)
		left_str = ft_calloc(1, 1);
	if (!left_str)
		return (NULL);
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(left_str, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buf), free(left_str), NULL);
		buf[bytes_read] = '\0';
		left_str = ft_strjoin(left_str, buf);
	}
	return (free(buf), left_str);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_readsave(fd, buf);
	if (!buf)
		return (NULL);
	line = ft_line(buf);
	buf = ft_next(buf);
	return (line);
}
