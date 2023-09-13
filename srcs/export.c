/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:44:31 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/12 18:41:02 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env(char **envp, char *str)
{
	int	i;

	i = 0;
	while (envp[i] && !is_env(envp[i], str))
	{
		i ++;
	}
	if (envp[i])
	{
		free(envp[i]);
		envp[i] = ft_strdup(str);
	}
}

void	ft_export2(char **envp, char **str, int i, int y)
{
	while (envp[i] && !is_env(envp[i], str[y]))
	{
		i ++;
	}
	if (envp[i] && is_in(str[y], '='))
	{
		free(envp[i]);
		envp[i] = ft_strdup(str[y]);
	}
	else if (!envp[i])
	{
		free(envp[i]);
		envp[i] = ft_strdup(str[y]);
		envp[i + 1] = 0;
	}
}

void	ft_export_empty(char **envp, int i)
{
	char	*quotes;

	while (envp[i])
	{
		if (envp[i][0] != '?')
		{
			quotes = ft_quote(envp[i]);
			printf("declare -x %s\n", quotes);
			free(quotes);
		}
		i ++;
	}
	return ;
}

void	ft_export(char **envp, char **str)
{
	int		i;
	int		y;

	y = 1;
	i = 0;
	if (str[1] == 0)
	{
		ft_export_empty(envp, i);
		return ;
	}
	while (str[y])
	{
		if (ft_isalpha(str[y][0]) && !is_in(str[y], '?'))
			ft_export2(envp, str, i, y);
		else
		{
			if (!(is_in(str[y], '?') && (ft_strlen(str[y]) < 2)))
				printf("minishell: export: `%s': not a valid identifier\n",
					str[y]);
		}
		y ++;
	}
}
