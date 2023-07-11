/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevers <tevers@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:15:06 by tevers            #+#    #+#             */
/*   Updated: 2023/07/11 05:32:21 by tevers           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>    /* SIZE_MAX libft */
# include <stdarg.h>    /* va_arg - printf */
# include <stdlib.h>    /* free, malloc libft */
# include <unistd.h>    /* write, pause - minitalk*/

char		*ft_itoa(int n);
				/* Returns a freeable string representing the int n */
int			ft_isalpha(int c); /* Checks if c is a alpha    */
int			ft_isdigit(int c); /* Checks if c is a digit    */
int			ft_isalnum(int c); /* Checks if c is a alphanum */
int			ft_isascii(int c); /* Checks if c is an ASCII character. */
int			ft_isprint(int c); /* Checks if c is a printable character. */
int			ft_tolower(int c); /* Returns c as lowercase equivalent */
int			ft_toupper(int c); /* Returns c as uppercase equivalent */
int			ft_atoi(const char *str);
				/* Convert a string to an int discards 
				leading whitespace, optional plus/minus */
char		*ft_strchr(char *s, int c);
				/* Returns the first occurence of "c" in "str" */
size_t		ft_strlen(const char *str); /* Returns the length of "str" */
void		ft_putnbr_fd(int n, int fd);
				/* Adds a signle digit as its 
				character representaion to the array */
char		*ft_strdup(const char *str); /* Returns a freeable copy of str */
void		ft_bzero(void *mem, size_t n); /* memset, sets mem to 0 for len n*/
void		ft_putchar_fd(char c, int fd);
				/* Outputs the char c to the file descriptor fd. */
char		**ft_split(char const *s, char c);
				/* Returns a array of freeable strings 
				obtained by spliting "str" with 'c'. */
char		*ft_strrchr(const char *s, int c);
				/* Returns the occurence of "c" in "str" */
void		ft_putstr_fd(const char *s, int fd);
				/* Outputs the string str to the file descriptor fd. */
void		ft_putendl_fd(const char *s, int fd);
				/* Outputs the string str to the file 
				descriptor fd followed by a new line. */
void		*ft_memset(void *mem, int c, size_t n);
				/* Sets "n" bytes from "mem" to "c" */
void		*ft_calloc(size_t nitems, size_t size);
				/* Allocates memory for "num" items with "size", 
				initialises to 0 */
void		*ft_memchr(const void *hay, int c, size_t n);
				/* Searches "n" bytes in "hay" for "c" 
				returning the first occurence */
char		*ft_strtrim(const char *str, const char *set);
				/* returns a freeable copy of "s" trimming 
				chars in set from front and back */
char		*ft_strjoin(char const *str1, char const *str2);
				/* Returns a freeable string which is the 
				concatination of str1 and str2 */
size_t		ft_strlcat(char *dest, const char *src, size_t n);
				/* strncat but null terminates result, 
				if dest > n, returns strl of str it tried to create */
size_t		ft_strlcpy(char *dest, const char *src, size_t n);
				/* strncpy but null terminates dest, size includes null */
void		*ft_memcpy(void *dest, const void *src, size_t n);
				/* Copies "n" bytes from memory area 
				"src" to memory area "dest" */
void		*ft_memmove(void *dest, const void *src, size_t n);
				/* Copies "n" bytes from memory area "src" 
				to memory area "dest" memory can overlap */
int			ft_strncmp(const char *s1, const char *s2, size_t n);
				/* Compares "n" characters from "str1" 
				with "str2" returns 0 or difference */
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
				/* Applies the function "f" to the index 
				and address of each character of "str" */
int			ft_memcmp(const void *mem1, const void *mem2, size_t n);
				/* Compares "n" bytes from "mem1" with 
				"mem2" returns 0 or difference */
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
				/* Returns a freeable string which is f 
				applied to every char + index of str */
char		*ft_strnstr(const char *hay, const char *needle, size_t n);
				/* Returns the first occurence of "needle" 
				in the first n characters of "hay" */
char		*ft_substr(char const *str, unsigned int start, size_t len);
				/* Returns a freeable copy of str starting 
				at start with size len */

/* ~ ~ ~ ~ ~ ~ GNL ~ ~ ~ ~ ~ ~ ~ */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char		*get_next_line(int fd);
			/* Reads and returns one line from fd, 
			every call of the function returns a new line till eof */
char		*ft_line_gnl(char *buf);
			/* Takes the full joined string and 
			splits it at newline (if it exists) */
char		*ft_next_gnl(char *buf);
		/* returns everything after the newline and frees the full string */
char		*ft_readsave_gnl(int fd, char *left_str);
				/* Reads and saves until newline is found or no byte is 
				read connects with previous leftovers from buf */

/* ~ ~ ~ ~ ~ ~ PRINTF ~ ~ ~ ~ ~ ~ */
int			ft_check_ptr_hex(unsigned long long n, char flag);
				/* checks if input is pointer or hex */
void		ft_print_ptr_hex(unsigned long long n, char flag);
				/* prints pointer and hex */
int			ft_check_flag(va_list args, const char flag);
				/* checks flag for int, char, string etc.
				and executes function added +colors*/
int			ft_print_ptr(unsigned long long ptr);
				/* just prints 0x and passes ptr */
char		*ft_toa(long nb, char *str, int len); /* converts nb to array */
int			ft_printf(const char *str, ...); /* my own printf */
int			ft_print_unbr(unsigned int n); /* prints unsigned int */
int			ft_print_str(char *str); /* check if str is empty */
int			ft_print_color(char c); /* DONT FORGET TO USE %e */
int			ft_print_char(int n); /* print char, return 1 */
int			ft_print_nbr(int n); /* uses itoa and strl */
int			ft_len(long nbr); /* counts the digits of nbr */
char		*ft_itoa_pf(int n);
				/* allocates a freeable str and passes nb & array toa */

#endif
