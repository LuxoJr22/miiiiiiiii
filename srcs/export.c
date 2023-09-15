/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:44:31 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/15 20:16:25 by sforesti         ###   ########.fr       */
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

char	**ft_export2(char **envp, char **str, int y)
{
	int		i;
	char	**ret;

	i = 0;
	while (envp[i] && !is_env(envp[i], str[y]))
		i ++;
	if (envp[i] && is_in(str[y], '='))
	{
		free(envp[i]);
		envp[i] = ft_strdup(str[y]);
	}
	else if (!envp[i])
	{
		ret = malloc(sizeof(char *) * (size_dptr(envp) + 2));
		i = 0;
		while (envp[i++])
			ret[i] = ft_strdup(envp[i]);
		ret[i] = ft_strdup(str[y]);
		ret[i + 1] = 0;
		free_dptr(envp);
		envp = ret;
	}
	return (envp);
}

void	ft_export_empty(char **envp)
{
	char	*quotes;
	int		i;

	i = 0;
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

char	**ft_export(char **envp, char **str)
{
	int		y;

	y = 1;
	if (str[1] == 0)
	{
		ft_export_empty(envp);
		return (envp);
	}
	while (str[y])
	{
		if (ft_isalpha(str[y][0]) && !is_in(str[y], '?'))
			envp = ft_export2(envp, str, y);
		else
		{
			if (!(is_in(str[y], '?') && (ft_strlen(str[y]) < 2)))
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(str[y], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				change_env(envp, "?=1");
			}
		}
		y ++;
	}
	return (envp);
}
