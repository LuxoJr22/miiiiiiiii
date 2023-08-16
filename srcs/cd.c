/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:42:38 by sforesti          #+#    #+#             */
/*   Updated: 2023/08/16 17:40:07 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_home(char	**envp)
{
	int		y;
	char	*path;

	y = index_env("OLDPWD", envp);
	envp[y] = ft_strjoin_f("OLDPWD=", getcwd(NULL, 0), 2);
	path = ft_getenv(envp, "HOME");
	chdir(path);
	y = index_env("PWD", envp);
	envp[y] = ft_strjoin_f("PWD=", getcwd(NULL, 0), 2);
	free (path);
	return ;
}

void	ft_cd(char *path, char **envp)
{
	DIR		*i;
	int		y;
	char	*ret;

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
		ret = ft_strjoin_f("Minishell: cd: ", path, 4);
		perror(ret);
		free(ret);
		return ;
	}
	y = index_env("OLDPWD", envp);
	free(envp[y]);
	envp[y] = ft_strjoin_f("OLDPWD=", getcwd(NULL, 0), 2);
	chdir(path);
	y = index_env("PWD", envp);
	free(envp[y]);
	envp[y] = ft_strjoin_f("PWD=", getcwd(NULL, 0), 2);
	free (i);
}
