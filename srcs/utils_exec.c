/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:33:52 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/14 13:46:59 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*acces_cmd(char *cmd)
{
	char	**path;
	char	*tmp_path;
	int		i;

	i = -1;
	if (!access(cmd, F_OK) && ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = ft_split(getenv("PATH"), ':');
	if (path == 0)
		return (ft_strdup(cmd));
	while (path[++i])
		path[i] = ft_strjoin_f(path[i], ft_strdup("/"), 3);
	i = -1;
	while (path[++i])
	{
		tmp_path = ft_strjoin_f(path[i], cmd, 4);
		if (!access(tmp_path, F_OK))
		{
			free_dptr(path);
			return (tmp_path);
		}
		free (tmp_path);
	}
	free_dptr(path);
	return (ft_strdup(cmd));
}

void	failed_exec(char *tmp, t_cmd *cmd, int fd[2])
{
	write(fd[1], "?=127", 6);
	close(fd[1]);
	tmp = ft_strjoin_f(ft_strjoin_f("Minishell: ",
				cmd->arg[0], 4), ": command not found\n", 1);
	ft_putstr_fd(tmp, 2);
	free(tmp);
	exit(127);
}

void	get_line(char **envp, int fd)
{
	char	buf[6];
	int		i;

	i = read(fd, buf, 6);
	if (i <= 0)
	{
		if (g_pid > 0)
			g_pid = -5;
		return ;
	}
	g_pid = -6;
	change_env(envp, buf);
}

void	child_process(t_cmd *cmd, char *tmp, int fd[2], char **envp)
{
	int	status;

	status = 0;
	if (cmd->in && cmd->in != -1)
		dup2(cmd->in, STDIN_FILENO);
	if (cmd->out && cmd->out != -1)
		dup2(cmd->out, STDOUT_FILENO);
	if (!cmd->here_doc)
		status = execve(cmd->name, cmd->arg, envp);
	if ((cmd->here_doc && !cmd->file->fd_file)
		|| (cmd->here_doc && cmd->file->type == 1))
		exit (1);
	if (status == -1)
		failed_exec(tmp, cmd, fd);
}

void	exec_cmd(t_cmd *cmd, char **envp, char *line)
{
	char	*tmp;
	int		fd[2];

	tmp = NULL;
	if (pipe(fd) == -1)
		return ;
	if (!count_pipe(line) || !cmd->arg[0])
		g_pid = fork();
	if (g_pid == 0)
		child_process(cmd, tmp, fd, envp);
	else
	{
		close(fd[1]);
		wait(NULL);
		get_line(envp, fd[0]);
	}
}
