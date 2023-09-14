/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:16:02 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/14 17:28:33 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *fd_file)
{
	char	*str;

	str = ft_strjoin_f("Minishell:", fd_file, 4);
	perror(str);
	free (str);
}

int	open_files_enter(t_cmd *cmd, t_file *file, char **envp)
{
	int	fd;

	fd = 0;
	if (file->type == 1)
	{
		fd = open (file->fd_file, O_RDONLY);
		if (fd == -1 && !cmd->here_doc)
		{
			error_msg(file->fd_file);
			change_env(envp, "?=1");
			cmd->here_doc = 1;
		}
	}
	if (file->type == 3)
	{
		fd = create_infile(file->fd_file, envp);
		if (fd == -1)
		{
			error_msg(file->fd_file);
			cmd->here_doc = 1;
		}
	}
	return (fd);
}

int	open_files_exit(t_cmd *cmd, t_file *file, char **envp)
{
	int	fd;

	fd = 0;
	if (file->type == 2)
	{
		fd = open (file->fd_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd == -1)
		{
			error_msg(file->fd_file);
			change_env(envp, "?=1");
			cmd->here_doc = 1;
		}
	}
	if (file->type == 4)
	{
		fd = open (file->fd_file, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (fd == -1)
		{
			error_msg(file->fd_file);
			change_env(envp, "?=1");
			cmd->here_doc = 1;
		}
	}
	return (fd);
}

void	redirection(t_cmd *cmd, t_file *file, char **envp)
{
	int	fd[2];

	fd[0] = 0;
	fd[1] = 0;
	while (file)
	{
		if (file->fd_file && (file->type == 1 || file->type == 3))
			fd[0] = open_files_enter(cmd, file, envp);
		if (file->fd_file && (file->type == 2 || file->type == 4))
			fd[1] = open_files_exit(cmd, file, envp);
		if (file->next
			&& (file->next->type == 1 || file->next->type == 3) && fd[0])
			close(fd[0]);
		if (file->next
			&& (file->next->type == 2 || file->next->type == 4) && fd[1])
			close(fd[1]);
		file = file->next;
	}
	cmd->in = fd[0];
	cmd->out = fd[1];
}
