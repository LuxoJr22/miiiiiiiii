/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:58:59 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/14 15:48:58 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnum(char *str)
{
	int i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

void	ft_exit(char **envp, char	*arg)
{
	int    i;

    i = 0;
    if (envp && envp[1])
        i = ft_atoi_f(arg) % 256;
    printf("exit\n");
    if (!arg || !ft_isnum(arg))
	{
    	ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	if (!ft_isnum(arg) && i == 0)
		i = 255;
	exit (i);
}
