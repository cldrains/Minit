/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:53:52 by tevers            #+#    #+#             */
/*   Updated: 2022/11/29 19:11:03 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (hay == needle || !*needle)
		return ((char *)hay);
	while (hay[i] && n > i)
	{		
		while (hay[i + j] == needle[j] && (i + j) < n && ft_strlen(hay) > i + j)
			j++;
		if (needle[j] == '\0')
			return ((char *)&hay[i]);
		if (!hay[j])
			return (NULL);
		j = 0;
		i++;
	}
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	char	find;
	size_t	i;

	last = (char *)s;
	find = (char)c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (last[i] == find)
			return (last + i);
		i--;
	}
	if (last[i] == find)
		return (last);
	return (0);
}

static int	check(const char c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(const char *str, char const *set)
{
	char	*strdone;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	if (!*str)
		return (ft_strdup(""));
	i = 0;
	j = ft_strlen(str) - 1;
	while ((check(str[i], set)) == 1)
		i++;
	if (i >= j)
		return (ft_strdup(""));
	while ((check(str[j], set)) == 1)
		j--;
	strdone = ft_substr(str, i, (j + 1 - i));
	return (strdone);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*s1;

	if (!*s)
		return (ft_strdup(""));
	i = 0;
	j = ft_strlen(s);
	if (len > j + start)
		len = j + start;
	s1 = ft_calloc(len + 1, sizeof(char));
	if (!s1)
		return (NULL);
	if (start > j)
		return (free (s1), ft_calloc(sizeof(char), 1));
	while (s[start + i] && i != len && i < j)
	{
		s1[i] = s[start + i];
		i++;
	}
	return (s1);
}
