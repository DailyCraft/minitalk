/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:41:23 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/29 16:45:22 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <libft.h>

int	g_has_received;

void	exit_kill_failure(void)
{
	ft_dprintf(2, "Failed to send signals!\n");
	ft_dprintf(2, "Please verify the server PID is correct.\n");
	exit(EXIT_FAILURE);
}

void	catch_signal(int sig)
{
	(void) sig;
	g_has_received = 1;
}

void	force_kill(int pid, int sig)
{
	int	i;

	g_has_received = 0;
	if (kill(pid, sig) != 0)
		exit_kill_failure();
	i = 0;
	while (!g_has_received)
	{
		usleep(10);
		i++;
		if (i > 10)
		{
			force_kill(pid, sig);
			return ;
		}
	}
}

void	send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i & 1) == 0)
			force_kill(pid, SIGUSR1);
		else
			force_kill(pid, SIGUSR2);
		i--;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc != 3)
	{
		ft_dprintf(2, "Invalid arguments!\n");
		ft_dprintf(2, "%s {server pid} {message}", argv[0]);
		return (EXIT_FAILURE);
	}
	signal(SIGUSR1, catch_signal);
	pid = ft_atoi(argv[1]);
	i = 0;
	while (argv[2][i])
	{
		send_char(pid, argv[2][i]);
		i++;
	}
	send_char(pid, 0);
}
