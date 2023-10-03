/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:58:59 by sforesti          #+#    #+#             */
/*   Updated: 2023/10/03 18:41:19 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i ++;
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
	if (i < 0)
		i = 256 - ((i * -1) % 256);
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
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		g_pid = -3;
		return ;
	}
	exit (i);
}

int	fill_envp(char **envn, char **envp, int i, int lvl)
{
	char	*str;

	while (envp[++i])
	{
		str = ft_cutenv(envp[i]);
		if (!strcmp("SHLVL", str))
			envn[i] = ft_strjoin_f("SHLVL=", ft_itoa(lvl + 1), 2);
		else
			envn[i] = ft_strdup(envp[i]);
		free(str);
	}
	return (i);
}
