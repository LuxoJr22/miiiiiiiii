/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:56:21 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/15 21:15:37 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_error(char **name, char **envp, int y)
{
	if (ft_strlen(name[y]) < 2)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(name[y], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		change_env(envp, "?=1");
	}
}

void	unset2(char **envp, int i)
{
	if (i)
	{
		free(envp[i - 1]);
		while (i != -1 && envp[i])
		{
			envp[i - 1] = envp[i];
			i ++;
		}
		if (i != -1)
			envp[i - 1] = 0;
	}
}

char	**ft_unset(char **name, char **envp)
{
	int	i;
	int	y;

	y = 1;
	i = 0;
	while (name[y])
	{
		if (!is_in(name[y], '?'))
		{
			i = index_env(name[y], envp) + 1;
			unset2(envp, i);
		}
		else if (!is_in(name[y], '?'))
			ft_unset_error(name, envp, y);
		y ++;
	}
	return (envp);
}
