/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 05:25:48 by tevers            #+#    #+#             */
/*   Updated: 2023/07/11 07:39:14 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H
# define BUFFER_SIZE_MT_C 10
# define BUFFER_SIZE_MT_S 20
# define SLEEP_TIME 80
# include "./libft/libft.h"
# include <signal.h>

typedef struct sigaction	t_sigaction;
unsigned char				*g_str_c;
unsigned char				*g_str_s;

unsigned char	*ft_join_mt(int len, int start,
					unsigned char *src, unsigned char *dst);
unsigned char	*ft_strjoin_c(unsigned char *s1, unsigned char *s2);
unsigned char	*ft_line_c(unsigned char *buf);
unsigned char	*get_next_line_c(unsigned char *str);
void			ft_handle_error_c(char *error, unsigned char *str);
void			ft_handle_success_c(
					unsigned char *tmp, int position, int max_lines);
void			ft_handler_helper_c(
					int signum, int *position, int s_pid, int max_lines);
void			ft_client_handler_c(
					int signum, siginfo_t *siginfo, void *sigcontext);
int				ft_line_end_c(unsigned char *buf, int len);
size_t			ft_lines_c(unsigned char *str);
int				ft_checksum_c(unsigned char *str);
int				ft_digit_to_pid(int number);
void			ft_send_null_c(int pid, unsigned char *str);
void			ft_print_status_c(int position, int max_lines, int width);
void			ft_send_str_c(int pid, unsigned char *str);
int				ft_check_input_c(int argc, char **argv);
void			ft_init_connection_c(int pid);

unsigned int	ft_atoi_s(unsigned char *str);
size_t			ft_strlen_s(const unsigned char *str);
int				ft_strnstr_s(unsigned char *hay,
					unsigned char *needle, size_t n);
int				ft_checksum_s(unsigned char *str);
void			ft_handle_error_s(char *error);
void			ft_handle_success_s(int c_pid);
void			ft_handler_helper_s(int c_pid, int *j);
void			ft_server_handler(int signum,
					siginfo_t *siginfo, void *sigcontext);
unsigned char	*ft_allocate_global_s(void);

#endif
