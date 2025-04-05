/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:14:32 by plichota          #+#    #+#             */
/*   Updated: 2025/04/06 01:47:35 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "libft.h"

volatile sig_atomic_t response = 0;

// converti char in 8 bit e lo salvo in bits
void  ascii_to_binary(char a, char *bits)
{
  int i;

  i = 7;
  bits[8] = '\0';
  while (i >= 0)
  {
    bits[i] = ((a >> (7 - i)) & 1) + '0';
    i--;
  }
  // printf("converted [%c] to [%s]\n", a, bits);
}

void  handler_sigaction(int signum, siginfo_t *info, void *context)
{
  (void) context;
  (void) info;
  if (signum == SIGUSR1)
  {
    // printf("Client: Ricevuto il segnale SIGUSR1 dal server!\n");
    printf("Il server ha ricevuto un bit!\n");
    response = 1;
  }
  // printf("ricevuto segnale: %d\n", signum);
  // printf("PID: %d\n", info->si_pid);
  // printf("UID: %d\n", info->si_uid);
  // printf("codice segnale: %d\n", info->si_code);
}

void  send_bit(int pid, int bool)
{
  if (!pid)
    return;
  if (bool)
  {
    printf("send 1\n");
    kill(pid, SIGUSR2);
  }
  else
  {
    printf("send 0\n");
    kill(pid, SIGUSR1);
  }
}

void  send_byte(int pid, char *bits)
{
  int i;
  int bit;

  i = 0;
  printf("----- MANDO PACCHETTO DI BIT %s\n", bits);
  while (i < 8)
  {
    bit = bits[i] - '0';
    response = 0;
    send_bit(pid, bit);
    while (!response)
      pause();
    i++;
  }
}

void  send_message(int pid, char *message)
{
  int i;
  char bits[9];

  i = 0;
  if (!message || !pid)
    return;
  while (message[i] != '\0')
  {
    ascii_to_binary(message[i], bits);
    // printf("[%c] %s\n", message[i], bits);
    // response = 0;
    send_byte(pid, bits);
    i++;
  }
}

// int is_valid_pid(char *pid)
// {
//   if 
// }

// int  send_ping (int pid)
// {
//   while (!response)
//   {
//     pause();
//   }
//   return (0);
// }

void  handle_error(int err)
{
  if (err == 1)
  {
    write(1, "Wrong usage\n", 12);
  }
  else {
    write(1, "Error\n", 6);
  }
}

int main(int argc, char *argv[])
{
  int pid;
  char *message;
  struct sigaction sa;

  ft_memset(&sa, 0, sizeof(sa));
  sa.sa_sigaction = handler_sigaction;
  sa.sa_flags = SA_SIGINFO;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGUSR1, &sa, NULL);

  if (argc == 3)
  {
    // if (!isValidPid(argv[1]))
    //   return (1);
    pid = ft_atoi(argv[1]);
    // if (!send_ping(pid))
    //   return (handle_error(0), 1);
    message = argv[2];
    send_message(pid, message);
  }
  else
  {
    return (handle_error(1), 1);
  }
}