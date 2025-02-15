/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usogukpi <usogukpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:59:41 by usogukpi          #+#    #+#             */
/*   Updated: 2025/02/14 15:03:28 by usogukpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "../printf_42/ft_printf.h"

void handle_signal(int sig, siginfo_t *info, void *context);

int main(void)
{
    struct sigaction sigact;

    ft_printf("Server PID: %d\n", getpid());
    sigemptyset(&sigact.sa_mask);
    sigact.sa_sigaction = handle_signal;
    sigact.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sigact, NULL);
    sigaction(SIGUSR2, &sigact, NULL);
    while (1)
        pause();
}

void handle_signal(int sig, siginfo_t *info, void *context)
{
    static int bit = 0;
    static char character = 0;

    (void)context;

    if (sig == SIGUSR2)
        character |= (1 << (7 - bit));
    bit++;
    if (bit == 8)
    {
        write(1, &character, 1);
        if (character == '\0')
            write(1, "\n", 1);
        bit = 0;
        character = 0;
    }
    kill(info->si_pid, SIGUSR1);
}
