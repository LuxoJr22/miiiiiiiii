/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:57:20 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/29 19:07:22 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(char *line)
{
	int	i;
	int	nbr_pipe;
	int	quote;

	i = -1;
	nbr_pipe = 0;
	quote = 0;
	while (line[++i])
	{
		if ((line[i] == 39 || line[i] == 34) && quote == 0)
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		if (line[i] == '|' && !quote)
			nbr_pipe ++;
	}
	return (nbr_pipe);
}

int	redirection_exit(t_cmd *cmd)
{
	close(cmd->fd[0]);
	dup2(cmd->fd[1], STDOUT_FILENO);
	close(cmd->fd[1]);
	return (0);
}

int	redirection_enter(t_cmd *cmd)
{
	dup2(cmd->fd[0], STDIN_FILENO);
	close (cmd->fd[0]);
	close (cmd->fd[1]);
	return (0);
}

int	exec_pipe(t_cmd *cmd, char **envp, char *line)
{
	if (cmd->next)
		if (pipe(cmd->fd) == -1)
			return (-1);
	g_pid = fork();
	if (g_pid == 0)
	{
		if (cmd->next)
			redirection_exit(cmd);
		get_command(cmd, envp, line);
		exit(1);
	}
	else
		redirection_enter(cmd);
	close (cmd->fd[1]);
	close (cmd->fd[0]);
	return (0);
}

int	manage_pipe(t_cmd *cmd, char **envp, char *line)
{
	int		stdout_fd;
	int		stdin_fd;
	int		status;
	char	*tp;

	tp = NULL;
	status = 0;
	stdout_fd = dup(STDOUT_FILENO);
	stdin_fd = dup(STDIN_FILENO);
	while (cmd)
	{
		exec_pipe(cmd, envp, line);
		cmd = cmd->next;
	}
	dup2(stdin_fd, 0);
	dup2(stdout_fd, 1);
	waitpid(g_pid, &status, 0);
	tp = ft_strjoin_f("?=", ft_itoa(status % 255), 2);
	change_env(envp, tp);
	while (wait(NULL) > 0)
		;
	free (tp);
	return (0);
}
