/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 02:30:48 by tevers            #+#    #+#             */
/*   Updated: 2023/07/11 09:06:06 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "Minitalk_bonus.h"

/*
Handles errors, and free g_str_c.
*/

void	ft_handle_error_c(char *error, unsigned char *str)
{
	ft_printf("Failed to send to PID, Server Down?\n-->%s%e", error);
	free(str);
	free(g_str_c);
	exit(EXIT_FAILURE);
}

/*
Function to handle after the string was send successfull
Updates loading bar, prints message, free's both strings.
*/

void	ft_handle_success_c(unsigned char *tmp, int position, int max_lines)
{
	ft_print_status_c(position, max_lines, 50);
	ft_printf("\n%g[              Message send Successfull            ]%e");
	free(tmp);
	free(g_str_c);
	exit(EXIT_SUCCESS);
}
/*
feed's tmp with get_next_line on first call,
if SIGUSR1 is recieved, it was send successfull
if SIGUSR2 is recieved, it failed and is resend
keep's track of the position to output the status
also if something is wrong it keeps track of the try
and aborts the function if it failed to often to send
*/

void	ft_handler_helper_c(int signum, int *position, int s_pid, int max_lines)
{
	static unsigned char	*tmp = NULL;

	if (tmp == NULL)
		tmp = get_next_line_c(g_str_c);
	if (signum == SIGUSR1)
	{
		if (tmp != NULL)
			free(tmp);
		tmp = NULL;
		*position += 1;
		tmp = get_next_line_c(g_str_c);
		if (tmp != NULL)
			ft_send_str_c(s_pid, tmp);
		else
			ft_handle_success_c(tmp, *position, max_lines);
	}
	else
		ft_send_str_c(s_pid, tmp);
}

/*
handles incoming signals
*/

void	ft_client_handler_c(int signum, siginfo_t *siginfo, void *sigcontext)
{
	static int	c_pid = 0;
	static int	s_pid = 0;
	static int	max_lines = 0;
	static int	position = 0;

	(void)sigcontext;
	if (c_pid == 0)
	{
		s_pid = siginfo->si_pid;
		c_pid = getpid();
		max_lines = ft_lines_c(g_str_c);
		ft_printf("%gConnection established! Sending messages to server\n");
		ft_printf("%gServer PID  <%i>  Client PID  <%i>", s_pid, c_pid);
		ft_printf("  Amount of Lines <%i>%e", max_lines);
	}
	ft_print_status_c(position, max_lines, 50);
	if (signum == SIGUSR1 || signum == SIGUSR2)
		ft_handler_helper_c(signum, &position, s_pid, max_lines);
}
