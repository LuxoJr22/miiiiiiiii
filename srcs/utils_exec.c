/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:33:52 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/05 23:38:43 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dptr(char	**dptr)
{
	int	i;

	i = -1;
	while (dptr[++i])
		free(dptr[i]);
	free(dptr);
}

char	*acces_cmd(char **envp, char *cmd)
{
	char	**path;
	char	*tmp_path;
	int		i;

	i = -1;
	(void)envp;
	if (!access(cmd, F_OK) && ft_strchr(cmd, '/'))
		return (cmd);
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
	return (cmd);
}

void	redirect_en_cmd_basic(t_file *file)
{
	int	fd;

	fd = 0;
	if (file->type == 1)
	{
		fd = open (file->fd_file, O_RDONLY);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", file->fd_file, 4));
			g_glob = 1;
			exit (errno);
		}
		dup2(fd, STDIN_FILENO);
	}
	if (file->type == 3)
	{
		fd = create_infile(file->fd_file);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", file->fd_file, 4));
			g_glob = 1;
			exit (errno);
		}
		dup2(fd, STDIN_FILENO);
	}
}

void	redirect_ex_cmd_basic(t_file *file)
{
	int	fd;

	fd = 0;
	if (file->type == 2)
	{
		fd = open (file->fd_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", file->fd_file, 4));
			g_glob = 1;
			exit(errno);
		}
		dup2(fd, STDOUT_FILENO);
	}
	if (file->type == 4)
	{
		fd = open (file->fd_file, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (fd == -1)
		{
			perror(ft_strjoin_f("Minishell: ", file->fd_file, 4));
			g_glob = 1;
			exit(errno);
		}
		dup2(fd, STDOUT_FILENO);
	}
}

void	exec_cmd(t_cmd *cmd, char **envp, char *line)
{
	pid_t	pid;
	int		status;
	char	*tmp;

	pid = 0;
	tmp = NULL;
	(void) line;
	if (!count_pipe(line) || !cmd->arg[0])
		pid = fork();
	status = 0;
	if (pid == 0)
	{
		g_glob = 1;
		dup2(cmd->in, STDIN_FILENO);
		dup2(cmd->out, STDOUT_FILENO);
		status = execve(cmd->name, cmd->arg, envp);
		if (status == -1)
		{
			tmp = ft_strjoin_f("Minishell: ", cmd->arg[0], 4);
			ft_putstr_fd(ft_strjoin_f(tmp, ": command not found\n", 1), 2);
			g_glob = 127;
			exit(0);
		}
	}
}
