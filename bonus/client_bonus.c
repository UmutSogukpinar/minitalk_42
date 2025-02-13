/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:59:44 by usogukpi          #+#    #+#             */
/*   Updated: 2025/02/13 16:49:00 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys/types.h"
#include "signal.h"
#include "../minitalk.h"
#include "../printf_42/ft_printf.h"
#include "unistd.h"
#include "stdlib.h"

volatile sig_atomic_t g_ack = 0;

static int  ft_atoi(const char *str);
static void ack_handler(int sig);
static void send_bit(char bit, pid_t pid);
static void send_messages(char *message, pid_t pid);

int main(int argc, char **argv)
{
    pid_t pid;
    struct sigaction sa;

    if (argc != 3)
    {
        ft_printf("Usage: %s <PID> <MESSAGE>\n", argv[0]);
        return (1);
    }
    
    pid = ft_atoi(argv[1]);
    if (pid <= 0)
    {
        ft_printf("Error: Invalid PID\n");
        return (1);
    }

    sa.sa_handler = ack_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &sa, NULL);

    send_messages(argv[2], pid);
    return (0);
}

void send_bit(char bit, pid_t pid)
{
    int current_bit = 7;

    while (current_bit >= 0)
    {
        g_ack = 0;
        
        if (bit & (1 << current_bit))
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        
        while (!g_ack)
            pause();
        
        current_bit--;
    }
}

static void send_messages(char *message, pid_t pid)
{
    int i;

    i = -1;
    while (message[++i])
    {
        send_bit(message[i], pid);
    }
    send_bit('\0', pid);
}

static void ack_handler(int sig)
{
    (void)sig;
    g_ack = 1;
}

static int ft_atoi(const char *str)
{
    int i;
    int sign;
    unsigned int acc;

    acc = 0;
    sign = 1;
    i = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        acc = acc * 10 + (str[i] - '0');
        i++;
    }
    return (sign * acc);
}
