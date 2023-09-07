/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:51:49 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/07 19:29:16 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_handle_ctrl_slash(int signal)
{
	(void)signal;
	if (g_pid > 0)
	{
		rl_redisplay();
		kill(g_pid, SIGTERM);
		g_pid = -1;
		write(1, "Quit\n", 5);
	}
}

void    ft_handle_ctrlc(int signal)
{
	(void)signal;
	if (g_pid < 0)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_pid > 0)
	{
		write(1, "^C\n", 3);
		kill(g_pid, SIGTERM);
		g_pid = -1;
	}
	else
	{
		write(1, "^C\n", 3);
		kill(g_pid, SIGTERM);
		g_pid = -1;
	}
}

void    ft_init_signals(void)
{
	struct termios    new;

	tcgetattr(0, &new);
	new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &new);
	signal(SIGQUIT, ft_handle_ctrl_slash);
	signal(SIGINT, ft_handle_ctrlc);
}
