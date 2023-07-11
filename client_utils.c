/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 02:21:48 by tevers            #+#    #+#             */
/*   Updated: 2023/07/11 04:28:30 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "Minitalk_bonus.h"

/*
makes sure that no utf8 char gets split
if there is one on the end of the string
*/

int	ft_line_end_c(unsigned char *buf, int len)
{
	int	utf;
	int	i;
	int	tmp;

	tmp = len;
	i = 0;
	utf = 0;
	while (i < len && buf[i])
	{
		if ((buf[i] & 0x80) == 0x00)
			utf = 1;
		else if ((buf[i] & 0xE0) == 0xC0)
			utf = 2;
		else if ((buf[i] & 0xF0) == 0xE0)
			utf = 3;
		else if ((buf[i] & 0xF8) == 0xF0)
			utf = 4;
		if (i + utf > len)
			return (tmp);
		i += utf;
		tmp = i;
		utf = 0;
	}
	return (tmp);
}

/*
count the amount of lines
*/

size_t	ft_lines_c(unsigned char *str)
{
	size_t		i;
	size_t		j;
	size_t		len;

	len = ft_strlen((const char *)str);
	i = 0;
	j = 0;
	while (len > i)
	{
		i += ft_line_end_c((unsigned char *)str + i, BUFFER_SIZE_MT_C);
		j++;
	}
	if (BUFFER_SIZE_MT_C > 9)
		j++;
	return (j);
}
/*
Calculates a checksum, for the Server output,
to compare the checksum wich is also calculated on the server,
to make sure the input matches exactly.
*/

int	ft_checksum_c(unsigned char *str)
{
	int	sum;

	sum = 1000000000;
	while (*str)
		sum += (unsigned char)*str++;
	return (sum);
}
/*
Makes sure the pid is 7 Digits long,
to Compare it on the Server side properly.
*/

int	ft_digit_to_pid(int number)
{
	if (number < 1000000)
		number += 1000000;
	return (number);
}
/*
Sends null
*/

void	ft_send_null_c(int pid, unsigned char *str)
{
	int	i;

	i = 0;
	while (i++ != 7)
	{
		usleep(SLEEP_TIME);
		if (kill(pid, SIGUSR2) == -1)
			ft_handle_error_c("%rSend Null failed%e", str);
	}
}
