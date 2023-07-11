/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:53:39 by tevers            #+#    #+#             */
/*   Updated: 2022/11/09 00:44:17 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int	i;
	int	j;

	i = ft_strlen(s);
	j = 0;
	if (!(char)c)
		return (&s[i]);
	if (!s)
		return (NULL);
	while (s[j] != '\0' && j < i)
	{
		if ((char) c == s[j])
			return (&s[j]);
		j++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s2;

	i = ft_strlen(s1);
	s2 = (char *)malloc(i + 1);
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1, i + 1);
	return (s2);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = -1;
	while (s[++i])
		f(i, &s[i]);
}

static char	*ft_join(int len, int start, const char *src, char *dst)
{
	int		i;
	int		j;

	j = 0;
	i = 0 + start;
	while (j < len)
		dst[i++] = src[j++];
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*together;
	int		len_s1;
	int		len_s2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	together = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!together)
		return (NULL);
	together = ft_join(len_s1, 0, s1, together);
	together = ft_join(len_s2, len_s1, s2, together);
	together[len_s1 + len_s2] = '\0';
	return (together);
}
