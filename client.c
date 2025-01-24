/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umut <umut@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:12:41 by umut              #+#    #+#             */
/*   Updated: 2025/01/24 16:20:56 by umut             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

static int	ft_atoi(const char *str);

int main(int arg_num, char **args)
{
	int	i;
	int	pid;

	if (arg_num != 3)
		exit(0);
	i = -1;
	pid = ft_atoi(args[2]);
	while (args[1][++i] != '\0')
		send_signal(pid, args[1][i]);
	
}

static void send_signal(int pid, char c)
{
	int	bit;
	int	max_bit;

	bit = -1;
	max_bit = 8;
	while (++bit < max_bit)
	{
		if (c & (0x01 << bit))
			kill();
	}
}

static int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}
