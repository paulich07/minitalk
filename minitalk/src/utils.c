/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:07:13 by plichota          #+#    #+#             */
/*   Updated: 2025/04/07 22:46:36 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	is_valid_pid(char *pid)
{
	int	i;

	i = 0;
	if (!pid || !*pid)
		return (0);
	while (pid[i] != '\0')
	{
		if (!ft_isdigit(pid[i]))
			return (0);
		i++;
	}
	return (1);
}

void	send_bit(int pid, int bool)
{
	if (!pid)
	{
		handle_error(0);
		return ;
	}
	if (bool)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
}

int	send_ping(int pid)
{
	if (kill(pid, 0) == 0)
		return (1);
	else
		return (0);
}

void	handle_error(int err)
{
	if (err == 1)
		write(1, "Wrong usage\n", 12);
	else if (err == 2)
		write(1, "Error: timeout exceeded\n", 24);
	else
		write(1, "Error\n", 6);
}
