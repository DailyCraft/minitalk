/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:42:03 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/29 16:49:23 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <libft.h>

static void	catch_signal(int sig, siginfo_t *info, void *ctx)
{
	static int	i = 7;
	static char	c = 0;

	(void) ctx;
	c |= (sig == SIGUSR2) << i;
	if (i == 0)
	{
		if (c == 0)
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd(c, 1);
		i = 7;
		c = 0;
	}
	else
		i--;
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("Server PID: %d\n", getpid());
	act.sa_sigaction = catch_signal;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
}
