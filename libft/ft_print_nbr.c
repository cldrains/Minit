/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 04:49:49 by tevers            #+#    #+#             */
/*   Updated: 2023/03/06 01:35:37 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(long nbr)
{
	int		len;

	len = 1;
	if (nbr == 0)
		return (len);
	while (nbr < 0 && len++)
		nbr = nbr * -1;
	while (nbr > 0 && len++)
		nbr = nbr / 10;
	return (--len);
}

char	*ft_toa(long nb, char *str, int len)
{
	if (nb == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		str[len--] = 48 + (nb % 10);
		nb = nb / 10;
	}
	return (str);
}

char	*ft_itoa_pf(int n)
{
	long	nb;
	int		len;
	char	*str;

	nb = n;
	len = ft_len(n);
	str = malloc(sizeof(char) * len + 1);
	str[len--] = '\0';
	str = ft_toa(nb, str, len);
	return (str);
}

int	ft_print_unbr(unsigned int nbr)
{
	char	*str;
	int		i;
	int		len;

	if (nbr == 0)
		return (ft_print_char('0'));
	len = ft_len(nbr);
	str = malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (nbr != 0)
	{
		str[--len] = nbr % 10 + 48;
		nbr = nbr / 10;
	}
	i = ft_print_str(str);
	return (free(str), i);
}

int	ft_print_nbr(int n)
{
	char	*nbr;
	int		len;

	nbr = ft_itoa(n);
	len = ft_print_str(nbr);
	return (free(nbr), len);
}
