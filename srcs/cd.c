/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:42:38 by sforesti          #+#    #+#             */
/*   Updated: 2023/10/04 12:16:22 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_home(char	**envp)
{
	int		y;
	char	*path;

	path = 0;
	y = index_env("OLDPWD", envp);
	if (y != -1)
	{
		free(envp[y]);
		envp[y] = ft_strjoin_f("OLDPWD=", getcwd(NULL, 0), 2);
	}
	if (index_env("HOME", envp) != -1)
		path = ft_getenv(envp, "HOME");
	chdir(path);
	y = index_env("PWD", envp);
	free(envp[y]);
	envp[y] = ft_strjoin_f("PWD=", getcwd(NULL, 0), 2);
	free (path);
	return ;
}

int	ft_cds(char **envp, char *path)
{
	DIR		*i;
	char	*ret;

	if (path == NULL)
	{
		go_home(envp);
		return (1);
	}
	if ((path[0] == 34 || path[0] == 39) && !path[1])
		return (1);
	i = opendir(path);
	if (i == NULL)
	{
		ret = ft_strjoin_f("Minishell: cd: ", path, 4);
		perror(ret);
		free(ret);
		g_pid = -3;
		return (1);
	}
	closedir(i);
	return (0);
}

void	ft_cd(char *path, char **envp)
{
	int		y;

	if (ft_cds(envp, path))
		return ;
	y = index_env("OLDPWD", envp);
	if (y != -1)
	{
		free(envp[y]);
		envp[y] = ft_strjoin_f("OLDPWD=", getcwd(NULL, 0), 2);
	}
	chdir(path);
	y = index_env("PWD", envp);
	free(envp[y]);
	envp[y] = ft_strjoin_f("PWD=", getcwd(NULL, 0), 2);
}
