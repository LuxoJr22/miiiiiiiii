/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:36:02 by sforesti          #+#    #+#             */
/*   Updated: 2023/10/03 18:58:21 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	verif_limiter(char *line, char *limiter)
{
	if (!ft_strcmp(line, limiter))
	{
		free (line);
		line = NULL;
		exit(0);
	}
}

char	*fd_to_str(int fd[2])
{
	char	*str;
	char	*line;

	str = get_next_line(fd[0]);
	line = get_next_line(fd[0]);
	while (line)
	{
		str = ft_strjoin_f(str, line, 3);
		line = get_next_line(fd[0]);
	}
	return (str);
}

int	check(t_cmd *cmd, char **envp)
{
	if (cmd->file && cmd->file->type == 3 && (!cmd->arg[0] || g_pid == -4))
	{
		if (g_pid == -3 || g_pid == -4)
			change_env(envp, "?=130");
		else
			change_env(envp, "?=0");
		return (1);
	}
	return (0);
}
