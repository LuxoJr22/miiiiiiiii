/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:42:38 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/05 23:23:34 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_home(char	**envp)
{
	int		y;
	int		i;
	int		u;
	char	*path;

	i = 5;
	u = 0;
	y = index_env(ft_strdup("OLDPWD"), envp);
	envp[y] = ft_strjoin(ft_strdup("OLDPWD="), ft_strdup(getcwd(NULL, 0)));
	y = index_env(ft_strdup("HOME"), envp);
	path = malloc(sizeof(char) * ft_strlen(envp[y]) - 4);
	while (envp[y][i])
	{
		path[u] = envp[y][i];
		u ++;
		i ++;
	}
	path[u] = '\0';
	chdir(path);
	y = index_env(ft_strdup("PWD"), envp);
	envp[y] = ft_strjoin(ft_strdup("PWD="), ft_strdup(getcwd(NULL, 0)));
	return ;
}

void	ft_cd(char *path, char **envp)
{
	DIR	*i;
	int	y;

	if (path == NULL)
	{
		go_home(envp);
		return ;
	}
	if ((path[0] == 34 || path[0] == 39) && !path[1])
		return ;
	i = opendir(path);
	if (i == NULL)
	{
		perror(ft_strjoin_f("Minishell: cd: ", path, 4));
		return ;
	}
	y = index_env(ft_strdup("OLDPWD"), envp);
	envp[y] = ft_strjoin(ft_strdup("OLDPWD="), ft_strdup(getcwd(NULL, 0)));
	chdir(path);
	y = index_env(ft_strdup("PWD"), envp);
	envp[y] = ft_strjoin(ft_strdup("PWD="), ft_strdup(getcwd(NULL, 0)));
}
