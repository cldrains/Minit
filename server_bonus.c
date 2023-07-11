/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 03:01:51 by tevers            #+#    #+#             */
/*   Updated: 2023/07/11 09:02:44 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minitalk_bonus.h"
#include "libft/libft.h"

unsigned char	*g_str_s;

/*
Handles and displays an error message, freeing memory and exiting the program.
Input: error - a string representing the error message.
*/

void	ft_handle_error_s(char *error)
{
	ft_printf("%rSomething is wrong here, Client Down?\n%s%e", error);
	if (g_str_s)
		free(g_str_s);
	exit(EXIT_FAILURE);
}

/* 
Function to handle the finish of the Message
*/

void	ft_handle_success_s(int c_pid)
{
	int	i;
	int	check;

	i = 9;
	g_str_s[BUFFER_SIZE_MT_S] = '\0';
	check = ft_strnstr_s(g_str_s + 10, (unsigned char *)"qNAF*4ag@9", 10);
	if (BUFFER_SIZE_MT_S > 19 && check == 1)
	{
		free(g_str_s);
		g_str_s = NULL;
		ft_printf("%g\nMessage recieved Successfull Client PID <%i>\n", c_pid);
		ft_printf("%bServer ready for new Input - Server PID <%i>%e", getpid());
	}
	else
		while (g_str_s[++i])
			write(1, &g_str_s[i], 1);
	if (kill(c_pid, SIGUSR1) == -1)
		ft_handle_error_s("SIGUSR1 Failed");
}

/*
Helper function to validate and process the recieved data.
Calculates the checksum of g_str_s and checks if it matches 
the first 10 characters If pass, prints the remaining portion 
of g_str_s and sends a SIGUSR1 to the client. If fail, sends
a SIGUSR2 signal to the client, and reset for new input
*/

void	ft_handler_helper_s(int c_pid, int *j)
{
	if (*j <= 9)
	{
		if (kill(c_pid, SIGUSR2) == -1)
			ft_handle_error_s("SIGUSR1 Failed");
	}
	else
	{
		if (ft_checksum_s(g_str_s))
			ft_handle_success_s(c_pid);
		else
			if (kill(c_pid, SIGUSR2) == -1)
				ft_handle_error_s("SIGUSR1 Failed");
	}
	if (*j < BUFFER_SIZE_MT_S + 1)
		*j = *j + 1;
	if (g_str_s)
		ft_memset(g_str_s, 0, *j);
	*j = 0;
}

/*
Purpose: Handles signals received by the server.
If the signal is SIGUSR1 or SIGUSR2, extracts bits from the signal to form 
characters and stores them in g_str_s.When a null character is encountered, 
calls ft_handler_helper_s to process the received data and reset g_str_s.
*/

void	ft_server_handler(int signum, siginfo_t *siginfo, void *sigcontext)
{
	static unsigned int		c = 0;
	static unsigned int		i = 0;
	static int				j = 0;
	static int				c_pid;

	(void)sigcontext;
	if (c_pid != siginfo->si_pid)
	{
		g_str_s = ft_allocate_global_s();
		c_pid = siginfo ->si_pid;
	}
	if (g_str_s)
	{
		if (signum == SIGUSR1)
			c |= (1 << i);
		if (++i == 8)
		{
			g_str_s[j++] = c;
			if (c == 0 || j == BUFFER_SIZE_MT_S + 1)
				ft_handler_helper_s(c_pid, &j);
			c = 0;
			i = 0;
		}
	}
}

/*
Allocates memory for g_str_s based on BUFFER_SIZE_MT_S.
Sets up the signal handler using sigaction for 
SIGINT, SIGQUIT, SIGUSR1, and SIGUSR2.
*/

int	main(void)
{
	t_sigaction	failsave;

	ft_memset(&failsave, 0, sizeof(failsave));
	ft_printf("%bServer waiting for new Input Server PID <%i>%e", getpid());
	failsave.sa_sigaction = ft_server_handler;
	sigemptyset (&failsave.sa_mask);
	failsave.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &failsave, NULL);
	sigaction(SIGUSR2, &failsave, NULL);
	while (1)
		pause();
}
