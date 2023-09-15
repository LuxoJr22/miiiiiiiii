/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:42:38 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/15 13:34:56 by sforesti         ###   ########.fr       */
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
	if (path == NULL)
	{
		go_home(envp);
		return (1);
	}
	if ((path[0] == 34 || path[0] == 39) && !path[1])
		return (1);
	return (0);
}

void	ft_cd(char *path, char **envp)
{
	DIR		*i;
	int		y;
	char	*ret;

	if (ft_cds(envp, path))
		return ;
	i = opendir(path);
	if (i == NULL)
	{
		ret = ft_strjoin_f("Minishell: cd: ", path, 4);
		perror(ret);
		free(ret);
		return ;
	}
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
	closedir(i);
}
