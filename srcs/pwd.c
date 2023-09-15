/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:54:40 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/15 17:19:52 by luxojr           ###   ########.fr       */
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

	y = 0;
	str = get_line_env(str, ret[0], envp);
	while (ret[y ++])
	{
		if (ret[y] && ret[y][0] == '?')
		{
			str = ft_strjoin_env(str, ft_getenv(envp, "?"), 3);
			env_name = ft_split(ret[y], '?');
			str = ft_strjoin_env(str, env_name[0], 1);
			free_dptr(env_name);
		}
		else
			str = ft_strjoin_env(str, ft_getenv(envp, ret[y]), 3);
	}
	free_dptr(ret);
	return (str);
}
