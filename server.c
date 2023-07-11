/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:44:13 by woosekim          #+#    #+#             */
/*   Updated: 2023/07/11 08:28:44 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk.h"

void	ft_s_handler(int signal)
{
	static int	bit;
	static char	c;

	if (signal == SIGUSR1)
		c = ((1 << bit) | c);
	if (signal == SIGUSR2)
		c = ((0 << bit) | c);
	bit++;
	if (bit == 8)
	{
		write(1, &c, 1);
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	ft_printf("%bServer waiting for new Input Server PID <%i>%e", getpid());
	signal (SIGUSR1, &ft_s_handler);
	signal (SIGUSR2, &ft_s_handler);
	while (1)
		pause();
	return (0);
}
