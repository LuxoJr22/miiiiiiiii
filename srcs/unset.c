/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:56:21 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/12 15:04:30 by luxojr           ###   ########.fr       */
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
		if (!is_in(name[y], '?'))
		{
			i = index_env(name[y], envp) + 1;
			free(envp[i - 1]);
			while (i != -1 && envp[i])
			{
				envp[i - 1] = envp[i];
				i ++;
			}
			if (i != -1)
				envp[i - 1] = 0;
		}
		else
		{
			if (ft_strlen(name[y]) < 2)
				printf("minishell: export: `%s': not a valid identifier\n", name[y]);			
		}
		y ++;
	}
}
