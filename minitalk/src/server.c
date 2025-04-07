/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:14:44 by plichota          #+#    #+#             */
/*   Updated: 2025/04/07 22:44:13 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	binary_to_ascii(char *s)
{
	char	a;
	int		i;
	int		bit;

	a = 0;
	i = 0;
	while (i < BUFFER_SIZE)
	{
		bit = s[i] - '0';
		a = (a << 1) | bit;
		i++;
	}
	return (a);
}

void	handler_sigaction(int sig, siginfo_t *info, void *context)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	static int	i = {0};
	char		a;

	(void) context;
	if (sig == SIGUSR1)
	{
		buffer[i++] = '0';
	}
	else if (sig == SIGUSR2)
	{
		buffer[i++] = '1';
	}
	if (i == BUFFER_SIZE)
	{
		buffer[BUFFER_SIZE] = '\0';
		a = binary_to_ascii(buffer);
		if (a)
			ft_putchar_fd(a, 1);
		i = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handler_sigaction;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
