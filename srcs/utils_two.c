/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:59:54 by sforesti          #+#    #+#             */
/*   Updated: 2023/08/29 14:23:09 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_union(char	**str)
{
	int		len;
	char	*ret;

	len = 0;
	ret = ft_strdup("");
	while (str[len])
	{
		if (is_in(str[len], '<') || is_in(str[len], '>'))
		{
			if ((int)ft_strlen(str[len]) == is_in(str[len], '<')
				|| (int)ft_strlen(str[len]) == is_in(str[len], '>'))
				len ++;
		}
		else
			ret = ft_strjoin_f(ft_strjoin_f(ret, str[len], 4), " ", 4);
		len ++;
	}
	return (ret);
}

void	free_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_file	*tp;

	tmp = NULL;
	tp = NULL;
	while (cmd)
	{
		tmp = cmd->next;
		while (cmd->file)
		{
			tp = cmd->file->next;
			if (cmd->file->fd_file && cmd->file->fd_file[0] != '\0')
				free(cmd->file->fd_file);
			free(cmd->file);
			cmd->file = tp;
		}
		if (cmd->arg && cmd->arg[0] && cmd->arg[0][0] != '\0')
			free_dptr(cmd->arg);
		if (cmd->name)
			free(cmd->name);
		free(cmd);
		cmd = tmp;
	}
}

int	size_dptr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
