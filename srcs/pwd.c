/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:54:40 by sforesti          #+#    #+#             */
/*   Updated: 2023/10/03 18:49:16 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **envp)
{
	char	*ret;

	ret = ft_getenv(envp, "PWD");
	printf("%s\n", ret);
	free(ret);
}

int	ft_atoi_f(char *str)
{
	int	i;
	int	negative;
	int	nb;

	i = 0;
	negative = 1;
	nb = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i ++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -1;
		i ++;
	}
	while (48 <= str[i] && str[i] <= 57 && str[i])
	{
		nb *= 10;
		nb += (str[i] - 48);
		i ++;
	}
	free(str);
	return (nb * negative);
}

char	*process_line(char *str, char **ret, char **envp)
{
	int		y;
	char	**env_name;

	y = -1;
	if (str[0] != '$')
		y ++;
	str = get_line_env(str, ret[0]);
	while (ret[++y])
	{
		if (ret[y])
		{
			env_name = ft_split(ret[y], ' ');
			str = ft_strjoin_env(str, ft_getenv(envp, env_name[0]), 3);
			str = ft_strjoin_f(str, ft_substr(ret[y],
						ft_strlen(env_name[0]), ft_strlen(ret[y])), 3);
			free_dptr(env_name);
		}
	}
	free_dptr(ret);
	return (str);
}

char	**env_change(char **envp, t_cmd *cmd)
{
	if (!cmd->here_doc && is_equal("export", cmd->name))
		envp = ft_export(envp, cmd->arg);
	else if (!cmd->here_doc && is_equal("unset", cmd->name))
		envp = ft_unset(cmd->arg, envp);
	return (envp);
}

int	ft_in_env(char *str, char **envp)
{
	char	**ret;
	char	*test;
	int		i;

	i = 0;
	if (str[0] == '$')
	{
		ret = ft_split(str, '$');
		while (ret[i])
		{
			test = ft_getenv(envp, ret[i]);
			if (test)
			{
				free_dptr(ret);
				free(test);
				return (1);
			}
			i ++;
		}
		free_dptr(ret);
		return (0);
	}
	return (1);
}
