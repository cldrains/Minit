/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 03:00:14 by tevers            #+#    #+#             */
/*   Updated: 2023/07/11 05:57:18 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "Minitalk_bonus.h"

size_t	ft_strlen_s(const unsigned char *str)
{
	size_t		i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str++ && i < BUFFER_SIZE_MT_S)
		i++;
	return (i);
}

/*
Finds the first occurrence of a substring within a given range of characters.
Changed to return either 0 or 1 to make sure Checknumber and Client PID matches.
*/

int	ft_strnstr_s(unsigned char *hay, unsigned char *needle, size_t n)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	haylen;

	i = 0;
	j = 0;
	if (hay == needle || !*needle || !*hay)
		return (0);
	haylen = ft_strlen_s(hay);
	if (haylen < 1)
		return (0);
	while (hay[i] && n > i)
	{
		while (hay[i + j] == needle[j] && (i + j) < n && haylen > i + j)
			j++;
		if (needle[j] == '\0')
			return (1);
		if (!hay[j])
			return (0);
		j = 0;
		i++;
	}
	return (0);
}

unsigned int	ft_atoi_s(unsigned char *str)
{
	unsigned int	nb;
	int				i;

	i = -1;
	nb = 0;
	while (str[++i] && i < 10)
	{
		if (str[i] > 58 || str[i] < 48)
			return (1337);
		nb = nb + str[i] - 48;
		if (i < 9)
			nb *= 10;
	}
	return (nb);
}

/*
Calculates a checksum, from the Client Input,
to compare the checksum wich is also calculated on the client,
to make sure the input matches exactly.
*/

int	ft_checksum_s(unsigned char *str)
{
	unsigned int	i;
	unsigned int	sum;
	unsigned int	check;

	i = 0;
	sum = 1000000000;
	if (!*str)
		return (0);
	check = ft_atoi_s(str);
	while (str && i != 10)
	{
		str++;
		i++;
	}
	while (*str && i++ < BUFFER_SIZE_MT_S)
		sum += (unsigned char)*str++;
	if (check == sum)
		return (1);
	else
		return (0);
}

unsigned char	*ft_allocate_global_s(void)
{
	unsigned char	*ret;

	ret = ft_calloc(BUFFER_SIZE_MT_S + 1, sizeof(unsigned char));
	if (!ret)
		ft_handle_error_s("Allocation failed");
	return (ret);
}
