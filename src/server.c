/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:14:44 by plichota          #+#    #+#             */
/*   Updated: 2025/04/06 01:47:34 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
#endif

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s != '\0')
	{
		s++;
		i++;
	}
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
	write(1, "\n", 1);
}

char binary_to_ascii(char *s)
{
	char a;
	int i;
	int bit;

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

void handler_sigaction(int sig, siginfo_t *info, void *context) {
	static char buffer[BUFFER_SIZE + 1] = {0};
	int i;
	int l;
	char a;
	(void) context;

	l = ft_strlen(buffer);
	// if (l > 0)
	// inserisce bit nel buffer
	if (l < BUFFER_SIZE)
	{
		if (sig == SIGUSR1) {
			printf("Received 0\n");
			buffer[l] = '0';
		} else if (sig == SIGUSR2) {
			printf("Received 1\n");
			buffer[l] = '1';
		}
		printf("buffer content:  %s\n\033[0m", buffer);
		// buffer[l + 1] = '\0';
	}
	l = ft_strlen(buffer);
	// se len 8 stampa char e libera buffer
	if (l == BUFFER_SIZE)
	{
		printf("buffer completo: %s: ", buffer);
		a = binary_to_ascii(buffer);
		if (a)
			ft_putchar(a);
		printf("\033[32m%c\n\033[0m", a);

		// printf("\033[31minizalizzo buffer\n\033[0m");
		i = 0;
		while (i < BUFFER_SIZE)
		{
			buffer[i] = 0;
			i++;
		}
		// Debugging
		l = ft_strlen(buffer);
		printf("buffer dopo: %s\n", buffer);
		printf("LUNGHEZZA buffer dopo: %d\n", l);
	}
	kill(info->si_pid, SIGUSR1);
}

int main() {
	struct sigaction sa;
	
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handler_sigaction;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	// METTERE FT_PRINTF
	printf("PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}