/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:56:21 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/05 02:56:34 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **name, char **envp)
{
	int	i;
	int	y;

	y = 1;
	while (name[y])
	{
		i = index_env(name[y], envp) + 1;
		while (i != -1 && envp[i])
		{
			envp[i - 1] = envp[i];
			i ++;
		}
		if (i != -1)
			envp[i - 1] = 0;
		y ++;
	}
}
