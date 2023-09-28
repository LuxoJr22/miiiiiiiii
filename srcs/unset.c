/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:56:21 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/29 00:18:12 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_error(char **name, char **envp, int y)
{
	if (ft_strlen(name[y]) < 2)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(name[y], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		change_env(envp, "?=1");
	}
}

void	unset2(char **envp, int i)
{
	if (i)
	{
		free(envp[i - 1]);
		while (i != -1 && envp[i])
		{
			envp[i - 1] = envp[i];
			i ++;
		}
		if (i != -1)
			envp[i - 1] = 0;
	}
}

char	**ft_unset(char **name, char **envp)
{
	int	i;
	int	y;

	y = 1;
	i = 0;
	while (name[y])
	{
		if (!is_in(name[y], '?'))
		{
			i = index_env(name[y], envp) + 1;
			unset2(envp, i);
		}
		else if (!is_in(name[y], '?'))
			ft_unset_error(name, envp, y);
		y ++;
	}
	return (envp);
}

void	process_redirect(char **envp, t_cmd *cmd)
{
	char	**ret;

	if (cmd->file)
	{
		if (is_in_quote(cmd->file->fd_file, '$') && cmd->file->type != 3)
		{
			cmd->file->fd_file = reset_quote(cmd->file->fd_file);
			if (!ft_in_env(cmd->file->fd_file, envp))
			{
				ft_putstr_fd("Minishell: ", 2);
				ft_putstr_fd(cmd->file->fd_file, 2);
				ft_putstr_fd(": ambiguous redirect\n", 2);
				cmd->here_doc = 1;
				cmd->file->type = 1;
				return ;
			}
			ret = ft_split(cmd->file->fd_file, '$');
			cmd->file->fd_file = process_line(cmd->file->fd_file, ret, envp);
		}
		else
			cmd->file->fd_file = reset_quote(cmd->file->fd_file);
	}
}

void	export_sort(char **envp, int i, int index)
{
	char	*str;

	str = ft_strdup(envp[index]);
	free(envp[index]);
	envp[index] = ft_strdup(envp[i]);
	free(envp[i]);
	envp[i] = str;
}
