/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:37:50 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/24 17:38:57 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_minishell(char *command, char **envp, t_cmd *cmd, char *line)
{
	if (is_equal("./minishell", command))
	{
		signal(SIGINT, fonction);
		signal(SIGQUIT, fonction);
	}
	exec_cmd(cmd, envp, line);
	if (!count_pipe(line) || command == NULL)
		waitpid(-1, NULL, 0);
	if (is_equal("./minishell", command))
	{
		signal(SIGINT, ft_handle_ctrlc);
		signal(SIGQUIT, ft_handle_ctrl_slash);
	}
}

void	fonction(int signal)
{
	(void)signal;
}
