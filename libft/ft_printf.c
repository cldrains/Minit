/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:13:47 by tevers            #+#    #+#             */
/*   Updated: 2023/07/11 05:33:28 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = -1;
	len = 0;
	va_start(args, str);
	while (str[++i])
	{
		if (str[i] == '%')
			len += ft_check_flag(args, str[++i]);
		else
			len += ft_print_char(str[i]);
	}
	va_end(args);
	return (len);
}

int	ft_check_flag(va_list args, const char flag)
{
	int	len;

	len = 0;
	if (flag == 'r' || flag == 'b' || flag == 'g'
		|| flag == 'y' || flag == 'w' || flag == 'n' || flag == 'e')
		len += ft_print_color(flag);
	else if (flag == 'c')
		len += ft_print_char(va_arg(args, int));
	else if (flag == 's')
		len += ft_print_str(va_arg(args, char *));
	else if (flag == 'p')
		len += ft_print_ptr(va_arg(args, unsigned long long));
	else if (flag == 'd' || flag == 'i')
		len += ft_print_nbr(va_arg(args, int));
	else if (flag == 'u')
		len += ft_print_unbr(va_arg(args, unsigned int));
	else if (flag == 'x' || flag == 'X')
		len += ft_check_ptr_hex(va_arg(args, int), flag);
	else if (flag == '%')
		len += ft_print_char('%');
	return (len);
}

int	ft_check_ptr_hex(unsigned long long n, char flag)
{
	int	i;

	i = 1;
	if (n == 0)
		return (ft_print_char('0'));
	if (flag == 'x' || flag == 'X')
		n = (unsigned int) n;
	ft_print_ptr_hex(n, flag);
	while (n != 0 && i++)
		n = n / 16;
	return (--i);
}

void	ft_print_ptr_hex(unsigned long long n, char flag)
{
	if (n >= 16)
	{
		ft_print_ptr_hex(n / 16, flag);
		ft_print_ptr_hex(n % 16, flag);
	}
	else
	{
		if ((flag == 'x' && n > 9) || (flag == 'p' && n > 9))
			ft_print_char(n + 87);
		else if (n > 9)
			ft_print_char(n + 55);
		else
			ft_print_char(n + 48);
	}
}

int	ft_print_ptr(unsigned long long ptr)
{
	int	len;

	len = ft_print_str("0x");
	return (len += ft_check_ptr_hex(ptr, 'p'));
}
