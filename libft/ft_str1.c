/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:53:41 by tevers            #+#    #+#             */
/*   Updated: 2023/07/11 05:33:11 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	destl;
	size_t	srcl;
	size_t	i;

	destl = ft_strlen(dest);
	srcl = ft_strlen(src);
	i = 0;
	if (n <= destl)
		return (n + srcl);
	n -= (destl + 1);
	while (src[i] && n--)
	{
		dest[destl + i] = src[i];
		i++;
	}
	dest[destl + i] = '\0';
	return (destl + srcl);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlen(const char *str)
{
	size_t		i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*s1;

	i = -1;
	s1 = ft_strdup(s);
	if (!s1 || !f)
		return (NULL);
	while (s1[++i])
		s1[i] = f(i, s1[i]);
	return (s1);
}

int	ft_strncmp(const char *str1, const char *str2, size_t i)
{
	while (i)
	{
		if (*str1 != *str2 || *str2 == '\0')
			return ((unsigned char)*str1 - (unsigned char)*str2);
		str1++;
		str2++;
		i--;
	}
	return (0);
}
