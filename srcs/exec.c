/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:07:17 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/29 19:04:41 by luxojr           ###   ########.fr       */
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

int	is_next_spaces(char *str, int i, char c)
{
	while (str[i])
	{
		if (!((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
			return (0);
		i ++;
		if (str[i] && (str[i] == '|'
				|| ((str[i] == '<' || str[i] == '>') && c != '|')))
			return (1);
	}
	return (1);
}

int	verif(char *line)
{
	int	i;

	i = -1;
	while (i == -1 || line[i])
	{
		i ++;
		if (line[i] == '|' && line[i + 1] == '|')
			return (-1);
		if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
			return (-2);
		if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
			return (-3);
		if ((line[i] == '<' || line[i] == '>' || line[i] == '|')
			&& is_next_spaces(line, i + 1, line[i]))
			return (-4);
		if (line[i] == 34)
			while (line[i] && line[++i] != 34)
				;
		if (line[i] == 39)
			while (line[i] && line[++i] != 39)
				;
	}
	return (0);
}

void	manage_exec(char *line, char **envp, t_cmd *cmd)
{
	if (cmd->next)
		manage_pipe(cmd, envp, line);
	else
		get_command(cmd, envp, line);
}

int	get_command(t_cmd *cmd, char **envp, char *line)
{
	char	*command;
	int		stdin_me;
	int		stdout_me;
	int		boolean;

	command = NULL;
	if (cmd->arg[0] != NULL)
		command = str_lower(cmd->arg[0]);
	stdin_me = dup(STDIN_FILENO);
	stdout_me = dup(STDOUT_FILENO);
	if (cmd->in && cmd->in != -1)
		dup2(cmd->in, STDIN_FILENO);
	if (cmd->out && cmd->out != -1)
		dup2(cmd->out, STDOUT_FILENO);
	boolean = built_in(command, cmd, envp, line);
	dup2(stdin_me, 0);
	dup2(stdout_me, 1);
	if (!boolean)
	{
		exec_cmd(cmd, envp, line);
		if (!count_pipe(line) || command == NULL)
			waitpid(-1, NULL, 0);
	}
	free(command);
	return (boolean);
}
