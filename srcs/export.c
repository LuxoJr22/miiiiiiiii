/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:44:31 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/05 02:44:45 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export2(char **envp, char **str, int i, int y)
{
	while (envp[i] && !is_env(envp[i], str[y]))
	{
		i ++;
	}
	if (envp[i])
		envp[i] = ft_strdup(str[y]);
	else
	{
		envp[i] = ft_strdup(str[y]);
		envp[i + 1] = 0;
	}
}

void	ft_export(char **envp, char **str)
{
	int		i;
	int		y;

	y = 1;
	i = 0;
	if (str[1] == 0)
	{
		while (envp[i])
		{
			printf("declare -x %s\n", ft_quote(envp[i]));
			i ++;
		}
		return ;
	}
	while (str[y])
	{
		if (ft_isalpha(str[y][0]))
			ft_export2(envp, str, i, y);
		else
			printf("minishell: export: `%s': not a valid identifier\n", str[y]);
		y ++;
	}
}
