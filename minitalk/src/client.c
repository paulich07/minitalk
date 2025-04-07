/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:14:32 by plichota          #+#    #+#             */
/*   Updated: 2025/04/07 22:41:10 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_response = 0;

void	handler_sigaction(int signum, siginfo_t *info, void *context)
{
	(void) context;
	(void) info;
	if (signum == SIGUSR1)
		g_response = 1;
	else
		g_response = 0;
}

int	wait_for_ack(int timeout_ms)
{
	int	waited;

	waited = 0;
	while (!g_response && waited < timeout_ms)
	{
		usleep(100);
		waited += 1;
	}
	return (g_response);
}

void	send_byte(int pid, char byte)
{
	int	i;
	int	bit;

	i = 7;
	while (i >= 0)
	{
		g_response = 0;
		bit = (byte >> i) & 1;
		send_bit(pid, bit);
		if (!wait_for_ack(5000))
		{
			handle_error(2);
			exit(EXIT_FAILURE);
		}
		i--;
	}
}

void	send_message(int pid, char *message)
{
	int	i;

	i = 0;
	if (!message || !pid)
		return ;
	while (message[i] != '\0')
	{
		send_byte(pid, message[i]);
		i++;
	}
	send_byte(pid, '\0');
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	char				*message;
	pid_t				pid;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handler_sigaction;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	if (argc == 3)
	{
		if (!is_valid_pid(argv[1]))
			return (ft_printf("Invalid PID\n"), 1);
		pid = ft_atoi(argv[1]);
		if (!send_ping(pid))
			return (ft_printf("Unreachable server\n"), 1);
		message = argv[2];
		send_message(pid, message);
	}
	else
	{
		return (handle_error(1), 1);
	}
}
