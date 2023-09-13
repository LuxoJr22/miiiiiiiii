/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:50:17 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/13 16:24:27 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_cmd *cmd)
{
	cmd->name = NULL;
	cmd->arg = NULL;
	cmd->fd[0] = 0;
	cmd->fd[1] = 0;
	cmd->file = 0;
	cmd->next = 0;
}

void	get_commands(char *line, t_cmd *cmd, char **envp)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = ft_split_parse(line, '|');
	while (cmds[i])
	{
		init_struct(cmd);
		cmd->arg = ft_split_parse(cmds[i], ' ');
		cmd->here_doc = 0;
		call_parsing_redir(cmd, line);
		pre_process(cmd->arg, envp);
		if (cmd->arg[0])
			cmd->name = acces_cmd(cmd->arg[0]);
		if (cmds[i + 1])
		{
			cmd->next = malloc(sizeof(t_cmd));
			cmd = cmd->next;
			cmd->file = 0;
		}
		i ++;
	}
	free_dptr(cmds);
	cmd->next = 0;
}

int	verif_line(char *line, char **envp)
{
	if (verif(line) == -1)
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `|'\n", 2);
		change_env(envp, "?=258");
		return (0);
	}
	if (verif(line) == -2)
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `>'\n", 2);
		change_env(envp, "?=258");
		return (0);
	}
	if (verif(line) == -3)
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `<'\n", 2);
		change_env(envp, "?=258");
		return (0);
	}
	if (verif(line) == -4)
	{
		ft_putstr_fd("Minishell: syntax error near unexpected \
		token `newline'\n", 2);
		change_env(envp, "?=258");
		return (0);
	}
	return (1);
}

t_cmd	*parsed_line(char *line, char **envp)
{
	t_cmd	*cmd;
	t_cmd	*begin_cmd;

	if (!verif_line(line, envp))
		return (0);
	cmd = malloc(sizeof(t_cmd));
	cmd->file = 0;
	get_commands(line, cmd, envp);
	begin_cmd = cmd;
	while (cmd)
	{
		redirection(cmd, cmd->file, envp);
		cmd = cmd->next;
	}
	return (begin_cmd);
}
