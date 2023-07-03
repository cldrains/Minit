#ifndef MINITALK_H
# define MINITALK_H
# include "./libft/libft.h"
#include <signal.h>

typedef struct sigaction    t_sigaction;
unsigned char               *c_str;
unsigned char               *s_str;

#define BUFFER_SIZE_MT_C 21
#define BUFFER_SIZE_MT_S (BUFFER_SIZE_MT_C + 10)
#define SLEEP_TIME 10
#endif
