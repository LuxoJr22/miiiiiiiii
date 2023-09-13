/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:33:52 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/12 23:58:20 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dptr(char **dptr)
{
	int	i;

	i = -1;
	while (dptr[++i])
		free(dptr[i]);
	free(dptr);
}

char	*free_dptr_line(char **dptr, char *str)
{
	char	*ret;

	ret = ft_strdup(str);
	free_dptr(dptr);
	return (ret);
}

char	*acces_cmd(char **envp, char *cmd)
{
	char	**path;
	char	*tmp_path;
	int		i;

	i = -1;
	(void)envp;
	if (!access(cmd, F_OK) && ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = ft_split(getenv("PATH"), ':');
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
	exit(1);
}

void	get_line(char **envp, int fd)
{
	char	buf[6];
	int		i;

	i = read(fd, buf, 6);
	if (i == -1)
		return ;
	change_env(envp, buf);
}

void	exec_cmd(t_cmd *cmd, char **envp, char *line)
{
	int		status;
	char	*tmp;
	int		fd[2];

	g_pid = 0;
	tmp = NULL;
	if (pipe(fd) == -1)
		return ;
	if (!count_pipe(line) || !cmd->arg[0])
		g_pid = fork();
	status = 0;
	if (g_pid == 0)
	{
		if (cmd->in && cmd->in != -1)
			dup2(cmd->in, STDIN_FILENO);
		if (cmd->out && cmd->out != -1)
			dup2(cmd->out, STDOUT_FILENO);
		if (!cmd->here_doc)
			status = execve(cmd->name, cmd->arg, envp);
		if ((cmd->here_doc && !cmd->file->fd_file)
			|| (cmd->here_doc && cmd->file->type == 1))
			exit (0);
		if (status == -1)
			failed_exec(tmp, cmd, fd);
	}
	else
	{
		close(fd[1]);
		wait(NULL);
		get_line(envp, fd[0]);
	}
}
