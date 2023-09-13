/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 08:15:45 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/12 19:37:21 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_name(char	**str, int mode)
{
	int		i;
	int		j;
	int		quote;

	i = -1;
	j = -1;
	quote = 0;
	while (str[++i])
	{
		while (str[i][++j])
		{
			if ((str[i][j] == 39 || str[i][j] == 34) && !quote)
				quote = str[i][j];
			else if (str[i][j] == quote)
				quote = 0;
			if (!quote && str[i][j] == '<' && mode == 1)
				return (i + 1);
			if (!quote && str[i][j] == '>' && mode == 2)
				return (i + 1);
		}
		j = -1;
	}
	return (-1);
}

t_file	*init_tfile(char *line)
{
	t_file	*file;

	(void)line;
	file = malloc(sizeof(t_file));
	file->fd_file = 0;
	file->type = 0;
	file->next = 0;
	return (file);
}

void	call_parsing_redir(t_cmd *cmd, char *line)
{
	char	*lines;

	if (find_name(cmd->arg, 1) != -1 || find_name(cmd->arg, 2) != -1)
	{
		manage_redirec(cmd, line);
		lines = ft_union(cmd->arg);
		free_dptr(cmd->arg);
		cmd->arg = ft_split(lines, ' ');
		free (lines);
	}
}

void	manage_redirec(t_cmd *cmd, char *line)
{
	int		coor[2];
	t_file	*file;

	coor[0] = 0;
	coor[1] = 0;
	cmd->file = init_tfile(line);
	file = cmd->file;
	choose_parsing(cmd, file, line, coor);
}
