/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:58:59 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/22 14:43:51 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

void	ft_exit(char **envp, char	**arg)
{
	int	i;

	i = 0;
	if (envp && envp[1] && arg[1])
		i = ft_atoi(arg[1]) % 256;
	printf("exit\n");
	if (arg[1] && !ft_isnum(arg[1]))
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit (255);
	}
	else if (arg[1] && arg[2])
	{
		ft_putstr_fd("Minishell: exit: : too many arguments\n", 2);
		exit (1);
	}
	if (arg[1] && !ft_isnum(arg[1]) && i == 0)
		i = 255;
	exit (i);
}
