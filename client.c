#include "libft/libft.h"
#include "Minitalk.h"

unsigned char *c_str;

static void ft_send_str(int pid, unsigned char *str);
void    ft_print_status(int position, int max_lines, int width, int try);


size_t	ft_strlen_mt(const unsigned char *str)
{
	size_t		i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

/*
makes sure that no utf8 char gets split
if there is one on the end of the string
*/

int ft_line_end(unsigned char *buf, int len)
{
    int utf;
    int i;
    int tmp;

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
Calculates a checksum, for the Server output,
to compare the checksum wich is also calculated on the server,
to make sure the input matches exactly.
*/

int ft_checksum_client(unsigned char *str)
{
    int sum;

    sum = 1000000000;
    while (*str)
        sum += (unsigned char)*str++;
    return(sum);
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
Joins two Strings
*/
static unsigned char	*ft_join_mt(int len, int start, unsigned char *src, unsigned char *dst)
{
	int     i;
	int		j;

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

unsigned char	*ft_strjoin_mt(unsigned char *s1, unsigned char *s2)
{
	unsigned char	*together;
	int		len_s1;
	int		len_s2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen_mt(s1);
	len_s2 = ft_strlen_mt(s2);
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
Part of the 'Get_next_line_mt' wich get the next freeable string
ready to send it to the server
*/

unsigned char *ft_line_mt(unsigned char *buf)
{
    int     i;
	int		validate_len;
    unsigned char    *line;

	i = ft_strlen_mt(buf);
	if (i == 0)
        return (NULL);
	validate_len = ft_line_end(buf, BUFFER_SIZE_MT_C);
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

unsigned char *get_next_line_mt(unsigned char *str)
{
    static unsigned char *buf = NULL;
    unsigned char        *line;
    static char i = 0;

    if (!buf)
        buf = str;
    line = ft_line_mt(buf);
    if (line)
    {
        buf += ft_strlen_mt(line);
        line = ft_strjoin_mt((unsigned char *)ft_itoa(ft_checksum_client(line)), line);
        return (line);
    }
    else if (!line && BUFFER_SIZE_MT_C > 9 && i == 0)
    {
        line = (unsigned char*)ft_strdup("qNAF*4ag@9");
        line = ft_strjoin_mt((unsigned char *)ft_itoa(ft_checksum_client(line)), line);
        i = 1;
        return (line);
    }
    else if (i-- == 1)
        return (buf = NULL);
    else
        return (NULL);
}

/*
Handles errors, and free's c_str.
*/
void ft_handle_error_c(char *error, unsigned char *str)
{
    ft_printf("Failed to send to PID, Server Down?\n-->%s%e", error);
    free(str);
    free(c_str);
    exit(EXIT_FAILURE);
}

/*
Keeps the Server alive, prevents it from freezing,
and start the connection, sends null to the server.
*/

void ft_send_null(int pid, unsigned char *str)
{
    int i = 0;
    while (i++ != 7)
    {
        usleep(SLEEP_TIME);
        if (kill(pid, SIGUSR2) == -1)
            ft_handle_error_c("%rSend Null failed%e", str);
    }
}

/*
Function to handle after the string was send successfull
Updates loading bar, prints message, free's both strings.
*/

void ft_handle_success_c(unsigned char *tmp, int position, int max_lines)
{
    ft_print_status(position, max_lines, 50, 1);
    ft_printf("\n%g[              Message send Successfull            ]%e");
    free(tmp);
    free(c_str);
    exit(EXIT_SUCCESS);
}

/*
Display the current Status in the Terminal
Eyecandy
*/

void    ft_print_status(int position, int max_lines, int width, int try)
{
    int i;
    int current_width;
    int percent;

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
        ft_printf("] 0%% <%i> Try: <%i>  \r", position, try);
    else
        ft_printf("] %i%% <%i> Try: <%i>  \r", percent, position, try);
}

/*
feed's tmp with get_next_line on first call,
if SIGUSR1 is recieved, it was send successfull
if SIGUSR2 is recieved, it failed and is resend
keep's track of the position to output the status
also if something is wrong it keeps track of the try
and aborts the function if it failed to often to send
*/

static void ft_handler_helper_c(int signum, int *retry, int *position, int s_pid, int max_lines)
{
    static char      		i = 0;
    static unsigned char	*tmp = NULL;

    if (i == 0)
    {
        tmp = get_next_line_mt(c_str);
        i = 1;
    }
    if (*retry > 421337)
        ft_handle_error_c("To many retry's, something wrong", tmp);
    if (signum == SIGUSR1)
    {
        if (tmp != NULL)
            free(tmp);
        *retry = 0;
        *position += 1;
        tmp = NULL;
        if ((tmp = get_next_line_mt(c_str)) != NULL)
            ft_send_str(s_pid, tmp);
        else
            ft_handle_success_c(tmp, *position, max_lines);
    }
    else
        ft_send_str(s_pid, tmp);
}

/*
handles incoming signals
*/

static void ft_client_handler(int signum, siginfo_t *siginfo, void *sigcontext)
{
    static int    c_pid = 0;
    static int    s_pid = 0;
    static int    retry = 0;
    static int    max_lines = 0;
    static int    position = 0;

	(void)sigcontext;
    if (c_pid == 0)
    {
        s_pid = siginfo->si_pid;
        c_pid = getpid();
        max_lines += ((float)ft_strlen_mt(c_str) / (float)BUFFER_SIZE_MT_C);
        max_lines = (int)max_lines;
        if ((float)ft_strlen_mt(c_str) / (float)BUFFER_SIZE_MT_C - (int)max_lines > 0)
            max_lines++;
        if (BUFFER_SIZE_MT_C > 9)
            max_lines++;
		ft_printf("%gConnection established! Currently sending messages to server\n");
        ft_printf("%gServer PID  <%i>  Client PID  <%i>  Amount of Lines <%i>%e", s_pid, c_pid, max_lines);
    }
    ft_print_status(position, max_lines, 50, ++retry);
    if (signum == SIGUSR1 || signum == SIGUSR2)
        ft_handler_helper_c(signum, &retry, &position, s_pid, max_lines);
}


/*
sends current string to pid
sends every bit of the char (8) by shifting left
and sending either 1 with SIGUSR1 or 0 with SIGUSR2
*/

static void ft_send_str(int pid, unsigned char *str)
{
	int i;
    int j;
    unsigned char c;

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
	ft_send_null(pid, str);
}

/*
checks input
*/

int ft_check_input_c(int argc, char **argv)
{
    int i;
    int pid;

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
        return (ft_printf("%r # PID can't be below 1 or above 4194304 # %e"), 0);
    if (argv[2][0] == '\0')
        return (ft_printf("%r # Expected Input is a String! # %e"), 0);
    return (pid);
}

void	ft_init_connection(int pid)
{
    int i;
	int j;

    i = 0;
	j = 0;
	while (j++ != BUFFER_SIZE_MT_S)
	{
		while (i++ != 8)
		{
			usleep(SLEEP_TIME);
			if (kill(pid, SIGUSR2) == -1)
			{
			    ft_printf("%rFailed to send to PID, Server Down?%e");
				free(c_str);
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

int main(int argc, char **argv)
{
    t_sigaction failsave;
    int pid;

    if (!(pid = ft_check_input_c(argc, argv)))
        return (ft_printf("%bUsage: ./client <SERVER_PID> <STRING_TO_SEND>%e"));
    c_str = (unsigned char*)ft_strdup(argv[2]);
    if (!c_str)
        return (0);
    ft_memset(&failsave, 0, sizeof(failsave));
    failsave.sa_sigaction = ft_client_handler;
    sigemptyset(&failsave.sa_mask);
    failsave.sa_flags = SA_RESTART | SA_SIGINFO;
    sigaction(SIGUSR1, &failsave, NULL);
    sigaction(SIGUSR2, &failsave, NULL);
    ft_init_connection(pid);
    while (1)
		pause();
}
