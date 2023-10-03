/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:50:17 by sforesti          #+#    #+#             */
/*   Updated: 2023/10/03 15:02:37 by luxojr           ###   ########.fr       */
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
	cmds = ft_split_parse(line, 1);
	while (cmds[i])
	{
		init_struct(cmd);
		cmd->arg = ft_split_parse(cmds[i], 2);
		cmd->here_doc = 0;
		call_parsing_redir(cmd, line);
		pre_process(cmd, envp);
		if (cmd->arg[0])
			cmd->name = acces_cmd(cmd->arg[0], envp);
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

char	*ft_strjoin_env(char *s1, char *s2, int mode)
{
	char	*r_str;
	size_t	i;
	size_t	j;

	r_str = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!r_str)
		return (NULL);
	j = -1;
	i = -1;
	while (s1 && s1[++i])
		r_str[i] = s1[i];
	while (s2 && s2[++j])
		r_str[i++] = s2[j];
	r_str[i] = '\0';
	if (mode == 1 || mode == 3)
		free(s1);
	if (mode == 2 || mode == 3)
		free(s2);
	return (r_str);
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
