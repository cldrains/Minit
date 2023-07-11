/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 04:21:13 by tevers            #+#    #+#             */
/*   Updated: 2023/07/11 05:34:27 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_strl(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_print_char(str[i]);
	return (i);
}

int	ft_print_str(char *str)
{
	if (str == NULL)
		return (ft_print_strl("(null)"));
	return (ft_print_strl(str));
}

int	ft_print_char(int c)
{
	return (write(1, &c, 1), 1);
}

int	ft_print_color(char flag)
{
	if (flag == 'e')
	{
		ft_printf("\033[0m");
		return (ft_print_char('\n'));
	}
	if (flag == 'n')
		ft_printf("\033[0m");
	if (flag == 'w')
		ft_printf("\033[0;47m");
	if (flag == 'g')
		ft_printf("\033[0;92m");
	if (flag == 'r')
		ft_printf("\033[1;37;41m");
	if (flag == 'y')
		ft_printf("\033[0;33m");
	if (flag == 'b')
		ft_printf("\033[0;94m");
	return (0);
}
