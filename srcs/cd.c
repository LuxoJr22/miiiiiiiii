/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:42:38 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/06 13:44:40 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_home(char	**envp)
{
	int		y;
	char	*path;

	y = index_env("OLDPWD", envp);
	envp[y] = ft_strjoin_f("OLDPWD=", getcwd(NULL, 0), 4);
	path = ft_getenv(envp, "HOME");
	chdir(path);
	y = index_env("PWD", envp);
	envp[y] = ft_strjoin_f("PWD=", getcwd(NULL, 0), 4);
	free (path);
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
	y = index_env("OLDPWD", envp);
	envp[y] = ft_strjoin_f("OLDPWD=", getcwd(NULL, 0), 4);
	chdir(path);
	y = index_env("PWD", envp);
	envp[y] = ft_strjoin_f("PWD=", getcwd(NULL, 0), 4);
	free (i);
}
