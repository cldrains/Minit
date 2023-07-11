/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 02:41:08 by tevers            #+#    #+#             */
/*   Updated: 2023/07/11 05:48:01 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "Minitalk_bonus.h"

unsigned char	*g_str_c;

/*
Display the current Status in the Terminal
Eyecandy
*/

void	ft_print_status_c(int position, int max_lines, int width)
{
	int	i;
	int	current_width;
	int	percent;

	i = 0;
	percent = position * 100 / max_lines;
	current_width = width * position / max_lines;
	if (percent > 100)
		percent = 100;
	if (current_width > 50)
		current_width = 50;
	ft_printf("%g[");
	while (i++ < current_width)
		ft_printf("■");
	while (i++ < width)
		ft_printf("□");
	if (percent < 1)
		ft_printf("] 0%% <%i>\r", position);
	else
		ft_printf("] %i%% <%i>\r", percent, position);
}
/*
sends current string to pid
sends every bit of the char (8) by shifting left
and sending either 1 with SIGUSR1 or 0 with SIGUSR2
*/

void	ft_send_str_c(int pid, unsigned char *str)
{
	int				i;
	int				j;
	unsigned char	c;

	i = 0;
	while (str[i])
	{
		c = str[i++];
		j = 0;
		while (j < 8)
		{
			usleep(SLEEP_TIME);
			if (c & (1 << j++))
			{
				if (kill(pid, SIGUSR1) == -1)
					ft_handle_error_c("SIGUSR1 Failed", str);
			}
			else
				if (kill(pid, SIGUSR2) == -1)
					ft_handle_error_c("SIGUSR2 Failed", str);
		}
	}
	ft_send_null_c(pid, str);
}

/*
checks input
*/

int	ft_check_input_c(int argc, char **argv)
{
	int	i;
	int	pid;

	if (BUFFER_SIZE_MT_C < 1)
		return (ft_printf("%r # Buffer Size cant be below 1 # %e"), 0);
	if (argc != 3)
		return (ft_printf("%r # Argument Count has to be 3! # ~ %e"), 0);
	i = 0;
	while (argv[1][i])
		if (!ft_isdigit(argv[1][i++]))
			return (ft_printf("%r ~ # PID contains only digits # %e"), 0);
	pid = ft_atoi(argv[1]);
	if (pid < 1 || pid > 4194304)
		return (ft_printf("%r # PID to low or high 4194304 is max # %e"), 0);
	if (argv[2][0] == '\0')
		return (ft_printf("%r # Expected Input is a String! # %e"), 0);
	return (pid);
}

void	ft_init_connection_c(int pid)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j++ < BUFFER_SIZE_MT_S)
	{
		while (i++ != 8)
		{
			usleep(SLEEP_TIME);
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_printf("%rFailed to send to PID, Server Down?%e");
				free(g_str_c);
				exit (EXIT_FAILURE);
			}
		}
	}
}

/*
main function, setting up signalhandler
sending null in while to keep the server alive and 
prevent it from freezing if a signal is lost 
wich triggers server to send a signal to SIGUSR2 
to resend the current string and clear on the server
the faulty input, also setting flags SIGINFO and SIGRESTART
to control the behavior of the programm if in the meantime
signals are incoming SIGRESTART is set, SIGINFO to use sigaction
*/

int	main(int argc, char **argv)
{
	t_sigaction	failsave;
	int			pid;

	pid = ft_check_input_c(argc, argv);
	if (!pid)
		return (ft_printf("%bUsage: ./client <SERVER_PID> <STRING_TO_SEND>%e"));
	g_str_c = (unsigned char *)ft_strdup(argv[2]);
	if (!g_str_c)
		return (0);
	ft_memset(&failsave, 0, sizeof(failsave));
	failsave.sa_sigaction = ft_client_handler_c;
	sigemptyset(&failsave.sa_mask);
	failsave.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &failsave, NULL);
	sigaction(SIGUSR2, &failsave, NULL);
	ft_init_connection_c(pid);
	while (1)
		pause();
}
