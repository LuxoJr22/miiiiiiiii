/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:58:59 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/05 03:02:40 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **envp, char	*arg)
{
	int	i;

	i = 0;
	if (envp && envp[1])
		i = ft_atoi(envp[1]) % 256;
	printf("exit\n");
	if (arg)
		printf ("Minishell: exit: %s: numeric argument required\n", arg);
	exit (i);
}
