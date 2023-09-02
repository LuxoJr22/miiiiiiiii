/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:07:17 by sforesti          #+#    #+#             */
/*   Updated: 2023/08/31 20:01:42 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_path(char **str)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_strjoin_f(str[0], " ", 4);
	while (str[++i])
	{
		line = ft_strjoin_f(line, str[i], 1);
		line = ft_strjoin_f(line, " ", 1);
	}
	return (line);
}

int	verif(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == '|' && line[i + 1] == '|'))
			return (-1);
		if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
			return (-2);
		if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
			return (-3);
		i ++;
		if (line[i] == 34)
			while (line[i] != 34)
				i++;
		if (line[i] == 39)
			while (line[i] != 39)
				i++;
	}
	return (0);
}

void	manage_exec(char *line, char **envp, t_cmd *cmd)
{
	if (verif(line) == -1)
	{
		printf ("Minishell: syntax error near unexpected token `|'\n");
		g_glob = 258;
		return ;
	}
	if (verif(line) == -2)
	{
		printf ("Minishell: syntax error near unexpected token `>'\n");
		g_glob = 258;
		return ;
	}
	if (verif(line) == -3)
	{
		printf ("Minishell: syntax error near unexpected token `<'\n");
		g_glob = 258;
		return ;
	}
	if (cmd->next)
		manage_pipe(cmd, envp, line);
	else
		get_command(cmd, envp, line);
}
