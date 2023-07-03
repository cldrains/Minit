#include "Minitalk.h"
#include "libft/libft.h"

unsigned char *s_str;


size_t	ft_strlen_mt(const unsigned char *str)
{
	size_t		i;

	i = 0;
    if (str == NULL)
            return (0);
	while (str++ && i < BUFFER_SIZE_MT_S)
		i++;
	return (i);
}

/*
Finds the first occurrence of a substring within a given range of characters.
Changed to return either 0 or 1 to make sure Checknumber and Client PID matches.
*/

static int ft_strnstr_mt(unsigned char *hay, unsigned char *needle, size_t n)
{
	unsigned int    i;
	unsigned int    j;
    unsigned int    haylen;

    i = 0;
    j = 0;
    if (hay == needle || !*needle || !*hay)
        return (0);
    haylen = ft_strlen_mt(hay);
    if (haylen < 1)
        return (0);
    while (hay[i] && n > i)
    {
        while (hay[i + j] == needle[j] && (i + j) < n && haylen > i + j)
            j++;
        if (needle[j] == '\0')
            return (1);
        if (!hay[j])
            return (0);
        j = 0;
        i++;
    }
    return (0);
}

/*
Handles and displays an error message, freeing memory and exiting the program.
Input: error - a string representing the error message.
*/

void    ft_handle_error_s(char *error)
{
    ft_printf("%rSomething is wrong here, Client Down?\n%s%e", error);
    if (s_str)
        free(s_str);
    exit(EXIT_FAILURE);
}

/* 
Function to handle the finish of the Message
*/

static void ft_handle_success_s(int c_pid)
{
    s_str[BUFFER_SIZE_MT_S] = '\0';
    if (BUFFER_SIZE_MT_S > 19 && ft_strnstr_mt(s_str + 10, (unsigned char*)"qNAF*4ag@9", 10))
    {
        free(s_str);
        s_str = NULL;
        ft_printf("%g\nMessage recieved Successfull from Client PID <%i>\n", c_pid);
        ft_printf("%bServer ready for new Input - - -  Server PID <%i>%e", getpid());
    }
    else
        ft_printf("%s", s_str + 10);
    if (kill(c_pid, SIGUSR1) == -1)
        ft_handle_error_s("SIGUSR1 Failed");
}

/*
Calculates a checksum, from the Client Input,
to compare the checksum wich is also calculated on the client,
to make sure the input matches exactly.
*/

static int	ft_checksum_s(unsigned char *str)
{
    unsigned int    i;
    unsigned int    sum;

    i = 0;
    sum = 1000000000;
    if (!*str)
        return (0);
    while (str && i != 10)
    {
        str++;
        i++;
    }
    while (*str && i++ < BUFFER_SIZE_MT_S)
        sum += (unsigned char)*str++;
    return (sum);
}

/*
Helper function to validate and process the recieved data.
Calculates the checksum of s_str and checks if it matches the first 10 characters.
Calculates the process ID of the client and checks if it matches the next 7 characters.
If both checks pass, prints the remaining portion of s_str and sends a SIGUSR1 signal to the client.
If either check fails, sends a SIGUSR2 signal to the client,
wich also happens when the client sends 0
*/

static void ft_handler_helper_s(int c_pid, int *j)
{
    unsigned int    check_sum;
    unsigned char   *tmp;

    if (*j <= 9)
    {
        if (kill(c_pid, SIGUSR2) == -1)
            ft_handle_error_s("SIGUSR1 Failed");
    }
    else
    {
        tmp = NULL;
        check_sum = 0;
        if ((tmp = (unsigned char *)ft_itoa(ft_checksum_s(s_str))) != NULL)
            check_sum = ft_strnstr_mt(s_str, tmp, 10);
        else
            ft_handle_error_s("Allocation Failed itoa");
        free(tmp);
        if (check_sum == 1)
            ft_handle_success_s(c_pid);
        else
            if (kill(c_pid, SIGUSR2) == -1)
                ft_handle_error_s("SIGUSR1 Failed");
    }
    if (s_str)
        ft_memset(s_str, 0, BUFFER_SIZE_MT_S);
    *j = 0;
}

void ft_server_handler_init(unsigned int *c, unsigned int *i, int *j)
{
    *c = 0;
    *i = 0;
    *j = 0;
}

/*
Purpose: Handles signals received by the server.
If the signal is SIGUSR1 or SIGUSR2, extracts bits from the signal to form 
characters and stores them in s_str.When a null character is encountered, 
calls ft_handler_helper_s to process the received data and reset s_str.
*/

static void	ft_server_handler(int signum, siginfo_t *siginfo, void *sigcontext)
{
    static unsigned int     c;
    static unsigned int     i;
    static int              j;
    static int              c_pid;

    (void)sigcontext;
    if (c_pid != siginfo->si_pid)
    {
        if (!(s_str = ft_calloc(BUFFER_SIZE_MT_S + 1, sizeof(char))))
            ft_handle_error_s("Allocation failed");
        c_pid = siginfo ->si_pid;
        ft_server_handler_init(&c, &i, &j);
    }
    if (s_str)
    {
        if (signum == SIGUSR1)
            c |= (1 << i);
        if (++i == 8)
        {
            s_str[j++] = c;
            if (c == 0 || j == BUFFER_SIZE_MT_S + 1)
                ft_handler_helper_s(c_pid, &j);
            c = 0;
            i = 0;
        }
    }
}

/*
Allocates memory for s_str based on BUFFER_SIZE_MT_S.
Sets up the signal handler using sigaction for 
SIGINT, SIGQUIT, SIGUSR1, and SIGUSR2.
*/

int main(void)
{
    t_sigaction failsave;
    if (BUFFER_SIZE_MT_C < 1)
        return (ft_printf("%r ~ # Buffer Size cant be below 1 # ~ %e"), 0);
    ft_memset(&failsave, 0, sizeof(failsave));
    ft_printf("%bServer waiting for new Input...   Server PID <%i>%e", getpid());
    failsave.sa_sigaction = ft_server_handler;
	sigemptyset (&failsave.sa_mask);
	failsave.sa_flags = SA_RESTART | SA_SIGINFO;
    sigaction(SIGUSR1, &failsave, NULL);
    sigaction(SIGUSR2, &failsave, NULL);
    while (1)
        pause();
}
