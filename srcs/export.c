/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:44:31 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/29 00:17:26 by luxojr           ###   ########.fr       */
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
		i = -1;
		while (envp[++i])
			ret[i] = ft_strdup(envp[i]);
		ret[i] = ft_strdup(str[y]);
		ret[i + 1] = 0;
		free_dptr(envp);
		envp = ret;
	}
	return (envp);
}

void	sort_empty(char	**envp)
{
	int		i;
	int		index;
	int		k;
	char	*str;

	i = 0;
	while (envp[i])
	{
		k = i;
		str = envp[k];
		index = k;
		while (envp[k])
		{
			if (ft_strcmp(str, envp[k]) > 0)
			{
				str = envp[k];
				index = k;
			}
			k ++;
		}
		if (i != k)
			export_sort(envp, i, index);
		i ++;
	}
}

void	ft_export_empty(char **envp)
{
	char	*quotes;
	char	**ret;
	int		i;

	i = -1;
	ret = malloc(sizeof(char *) * (size_dptr(envp) + 1));
	while (envp[++i])
		ret[i] = ft_strdup(envp[i]);
	ret[i] = 0;
	sort_empty(ret);
	i = 0;
	while (ret[i])
	{
		if (ret[i][0] != '?')
		{
			quotes = ft_quote(ret[i]);
			printf("declare -x %s\n", quotes);
			free(quotes);
		}
		i ++;
	}
	free_dptr(ret);
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
