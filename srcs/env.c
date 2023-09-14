/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:28:13 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/14 17:45:47 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cutenv(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != '=')
		i ++;
	ret = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		ret[i] = str[i];
		i ++;
	}
	ret[i] = '\0';
	return (ret);
}

int	is_env(char	*env, char	*str)
{
	char	*strr;
	char	*envr;
	int		i;

	strr = ft_cutenv(str);
	envr = ft_cutenv(env);
	i = (ft_strncmp(strr, envr, ft_strlen(strr)) == 0
			&& ft_strncmp(strr, envr, ft_strlen(envr)) == 0);
	free(strr);
	free(envr);
	return (i);
}

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (is_in(envp[i], '=') && envp[i][0] != '?')
			printf("%s\n", envp[i]);
		i ++;
	}
}

int	index_env(char *name, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (is_env(name, envp[i]))
			return (i);
		i ++;
	}
	return (-1);
}

char	*ft_getenv(char **envp, char *str)
{
	int		i;
	int		o;
	char	**line;

	i = -1;
	while (str && envp[++i])
	{
		o = 0;
		line = ft_split(envp[i], '=');
		while (line[o])
			o ++;
		if (o > 1)
		{
			o = 2;
			while (line[o])
				line[1] = ft_strjoin_f(ft_strjoin_f(line[1], "=", 1),
						line[o++], 1);
		}
		if (!ft_strncmp(line[0], str, ft_strlen(line[0]))
			&& !ft_strncmp(line[0], str, ft_strlen(str)))
			return (free_dptr_line(line, line[1]));
		if (line && line[0] && line[0][0])
			free_dptr(line);
	}
	return (0);
}
