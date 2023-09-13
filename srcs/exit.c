/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:58:59 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/13 16:14:31 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **envp, char	*arg)
{
	int	i;

	i = 0;
	if (envp && envp[1])
		i = ft_atoi(ft_getenv(envp, "?"));
	printf("exit\n");
	if (arg)
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	exit (i);
}
