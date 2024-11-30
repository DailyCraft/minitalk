/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:42:03 by dvan-hum          #+#    #+#             */
/*   Updated: 2024/11/30 12:59:34 by dvan-hum         ###   ########.fr       */
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

	ft_printf("\033[1;33mServer PID: \033[1;32m%d\033[0m\n", getpid());
	act.sa_sigaction = catch_signal;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
}
