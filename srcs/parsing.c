/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:50:17 by sforesti          #+#    #+#             */
/*   Updated: 2023/08/31 17:13:58 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_quote_two(int quote, char *str, char	*ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!quote && (str[i] == 34 || str[i] == 39))
			quote = str[i++];
		else if (quote == str[i])
		{
			quote = 0;
			i ++;
		}
		ret[j] = str[i];
		if (str[i])
		{
			i ++;
			j ++;
		}
	}
	ret[j] = 0;
	free(str);
}

char	*reset_quote(char *str)
{
	int		i;
	int		j;
	int		quote;
	char	*ret;

	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == 34 || str[i] == 39))
		{
			quote = str[i];
			j ++;
		}
		else if (quote == str[i])
		{
			quote = 0;
			j ++;
		}
		i ++;
	}
	ret = malloc(sizeof(char) * (i - j) + 1);
	reset_quote_two(quote, str, ret);
	return (ret);
}

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
	char	*lines;

	i = 0;
	cmds = ft_split_parse(line, '|');
	lines = NULL;
	while (cmds[i])
	{
		init_struct(cmd);
		cmd->arg = ft_split_parse(cmds[i], ' ');
		cmd->here_doc = 0;
		call_parsing_redir(cmd, lines, line);
		pre_process(cmd->arg, envp);
		cmd->name = ft_strdup(acces_cmd(envp, cmd->arg[0]));
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

t_cmd	*parsed_line(char *line, char **envp)
{
	t_cmd	*cmd;
	t_cmd	*begin_cmd;

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
