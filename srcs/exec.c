/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:07:17 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/11 18:07:36 by luxojr           ###   ########.fr       */
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
		change_env(envp, "?=258");
		return ;
	}
	if (verif(line) == -2)
	{
		printf ("Minishell: syntax error near unexpected token `>'\n");
		change_env(envp, "?=258");
		return ;
	}
	if (verif(line) == -3)
	{
		printf ("Minishell: syntax error near unexpected token `<'\n");
		change_env(envp, "?=258");
		return ;
	}
	if (cmd->next)
		manage_pipe(cmd, envp, line);
	else
		get_command(cmd, envp, line);
}

void	get_command(t_cmd *cmd, char **envp, char *line)
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
	boolean = built_in(command, cmd, envp);
	dup2(stdin_me, 0);
	dup2(stdout_me, 1);
	if (!boolean)
	{
		exec_cmd(cmd, envp, line);
		if (!count_pipe(line) || command == NULL)
			waitpid(-1, NULL, 0);
	}
	g_pid = -1;
	free(command);
}
