/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:51:49 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/07 17:22:21 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit(int i)
{
	(void)i;
	if (g_glob == 1)
	{
		write(1, "\b", 1);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_ctrl(void)
{
	struct termios	new;

	tcgetattr(0, &new);
	new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new);
}

void	interrupt(int i)
{
	(void)i;
	kill(-15, SIGINT);
	write(1, "\b", 1);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
