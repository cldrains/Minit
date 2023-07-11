/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 02:36:47 by tevers            #+#    #+#             */
/*   Updated: 2023/07/11 05:41:42 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "Minitalk_bonus.h"

/*
Joins two Strings
*/
unsigned char	*ft_join_mt(int len, int start,
	unsigned char *src, unsigned char *dst)
{
	int	i;
	int	j;

	j = 0;
	i = 0 + start;
	while (j < len)
		dst[i++] = src[j++];
	return (dst);
}

/*
Changed ft_strjoin wich also free's the Input
to prevent Memory leaks.
*/

unsigned char	*ft_strjoin_c(unsigned char *s1, unsigned char *s2)
{
	unsigned char	*together;
	int				len_s1;
	int				len_s2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen((const char *)(s1));
	len_s2 = ft_strlen((const char *)(s2));
	together = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!together)
		return (NULL);
	together = ft_join_mt(len_s1, 0, s1, together);
	together = ft_join_mt(len_s2, len_s1, s2, together);
	together[len_s1 + len_s2] = '\0';
	free (s1);
	free (s2);
	return (together);
}
/*
Part of the 'get_next_line_c' wich get the next freeable string
ready to send it to the server
*/

unsigned char	*ft_line_c(unsigned char *buf)
{
	int				i;
	int				validate_len;
	unsigned char	*line;

	i = ft_strlen((const char *)buf);
	if (i == 0)
		return (NULL);
	validate_len = ft_line_end_c(buf, BUFFER_SIZE_MT_C);
	if (i > BUFFER_SIZE_MT_C)
		i = validate_len;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (i--)
		line[i] = buf[i];
	return (line);
}
/*
Creating a freeable String and outputs the 'next string to send to the server'
Wich includes first the checksum and then the client pid
wich both get compared on the server side to make 100% sure
the String send matches the string recieved.
*/

unsigned char	*get_next_line_c(unsigned char *str)
{
	static unsigned char	*buf = NULL;
	unsigned char			*line;
	static char				i = 0;

	if (!buf)
		buf = str;
	line = ft_line_c(buf);
	if (line)
	{
		buf += ft_strlen((const char *)line);
		line = ft_strjoin_c((unsigned char *)
				ft_itoa(ft_checksum_c(line)), line);
		return (line);
	}
	else if (!line && BUFFER_SIZE_MT_C > 9 && i == 0)
	{
		line = (unsigned char *)ft_strdup("qNAF*4ag@9");
		line = ft_strjoin_c((unsigned char *)
				ft_itoa(ft_checksum_c(line)), line);
		i = 1;
		return (line);
	}
	else
		return (NULL);
}
