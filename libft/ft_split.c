/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:31:52 by tevers            #+#    #+#             */
/*   Updated: 2022/11/26 11:25:24 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_split_len(const char *s, const char c, size_t j)
{
	size_t	i;

	i = 0;
	while (s[i + j] != c && s[i + j])
		i++;
	return (i);
}

static size_t	ft_count_splits(const char *s, const char c)
{
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
	while (*s)
	{
		if (*s != c && j == 0 && i++)
			j = 1;
		else if (*s == c)
			j = 0;
		s++;
	}
	return (--i);
}

static char	**ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

static char	*ft_fill_split(const char *str, size_t len, size_t count)
{
	size_t		i;
	char		*ret;

	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (len > i)
	{
		ret[i] = (char) str[count + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		j;
	char		**ret;

	ret = ft_calloc(ft_count_splits(s, c) + 1, sizeof(char *));
	if (!ret)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			ret[j] = ft_fill_split(s, ft_split_len(s, c, i), i);
			if (!ret[j])
				return (ft_free(ret));
			i += ft_strlen(ret[j++]);
		}
	}
	return (ret);
}
