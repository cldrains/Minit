/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:44:17 by woosekim          #+#    #+#             */
/*   Updated: 2023/07/11 08:45:49 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk.h"

void	ft_send_char_client(int pid, char c)
{
	int	bit;

	bit = -1;
	while (++bit <= 7)
	{
		usleep(SLEEP_TIME);
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
	}
}

int	ft_check_input_client(int argc, char **argv)
{
	int	i;
	int	pid;

	if (argc != 3)
		return (ft_printf("%r # Argument Count has to be 3! # ~ %e"), 0);
	i = 0;
	while (argv[1][i])
		if (!ft_isdigit(argv[1][i++]))
			return (ft_printf("%r # PID contains only digits # %e"), 0);
	pid = ft_atoi(argv[1]);
	if (pid < 1 || pid > 4194304)
		return (ft_printf("%r # PID to low or high 4194304 is max # %e"), 0);
	if (argv[2][0] == '\0')
		return (ft_printf("%r # Expected Input is a String! # %e"), 0);
	return (pid);
}

int	main(int argc, char **argv)
{
	int	i;
	int	pid;

	pid = ft_check_input_client(argc, argv);
	if (!pid)
		return (ft_printf("%bUsage: ./client <SERVER_PID> <STRING_TO_SEND>%e"));
	i = -1;
	while (argv[2][++i])
		ft_send_char_client(pid, argv[2][i]);
	ft_printf("%g[  Message send compeltely to PID <%i>  ]%e", pid);
	return (0);
}
