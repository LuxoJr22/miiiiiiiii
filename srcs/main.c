/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:25:01 by mboyer            #+#    #+#             */
/*   Updated: 2023/09/14 16:30:59 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in(char *command, t_cmd *cmd, char **envp)
{
	if (!cmd->here_doc && is_equal("echo", command))
		ft_echo(cmd->arg);
	else if (!cmd->here_doc && is_equal("pwd", command))
		ft_pwd(envp);
	else if (!cmd->here_doc && is_equal("export", command))
		ft_export(envp, cmd->arg);
	else if (!cmd->here_doc && is_equal("env", command) && !cmd->arg[1])
		ft_env(envp);
	else if (!cmd->here_doc && is_equal("exit", command))
		ft_exit(envp, cmd->arg[1]);
	else if (!cmd->here_doc && is_equal("unset", command))
		ft_unset(cmd->arg, envp);
	else if (!cmd->here_doc && is_equal("cd", command))
		ft_cd(cmd->arg[1], envp);
	else
		return (0);
	return (1);
}

char	**pre_process(char **str, char **envp)
{
	int		i;
	int		y;
	char	**ret;

	i = -1;
	y = 1;
	while (str[++i])
	{
		if (is_in_quote(str[i], '$'))
		{
			str[i] = reset_quote(str[i]);
			ret = ft_split(str[i], '$');
			str[i] = get_line_env(str[i], ret[0], envp);
			while (ret[y++])
				str[i] = ft_strjoin_f(str[i], ft_getenv(envp, ret[y]), 3);
			y = 1;
			free_dptr(ret);
		}
		else
			str[i] = reset_quote(str[i]);
	}
	return (NULL);
}

char	**init_env(char **envp)
{
	char	**envn;
	int		i;

	i = -1;
	if (!size_dptr(envp))
	{
		envn = malloc(sizeof(char *) * (5));
		envn[0] = ft_strdup("PWD=/home/luxojr/project/mini");
		envn[1] = ft_strdup("SHLVL=1");
		envn[2] = ft_strdup("_=/usr/bin/env");
		i = 3;
	}
	else
	{
		envn = malloc(sizeof(char *) * (size_dptr(envp) + 2));
		while (envp[++i])
			envn[i] = ft_strdup(envp[i]);
	}
	envn[i] = ft_strdup("?=0");
	envn[i + 1] = 0;
	return (envn);
}

char	*loop(char **envn, char *oui, t_cmd *cmd)
{
	free(oui);
	oui = readline("Minishell>");
	if (g_pid == -5)
		change_env(envn, "?=0");
	if (g_pid == -2)
		change_env(envn, "?=131");
	if (g_pid == -3)
		change_env(envn, "?=1");
	if (g_pid == -4)
		change_env(envn, "?=130");
	if (oui && *oui)
	{
		add_history(oui);
		cmd = parsed_line(oui, envn);
		if (cmd)
			manage_exec(oui, envn, cmd);
		free_list(cmd);
	}
	else
		change_env(envn, "?=0");
	return (oui);
}

int	main(int ac, char **av, char **envp)
{
	char		*oui;
	t_cmd		*cmd;
	char		**envn;
	int			i;

	(void) ac;
	(void) av;
	g_pid = -1;
	i = 0;
	ft_init_signals();
	envn = init_env(envp);
	cmd = NULL;
	oui = getcwd(NULL, 0);
	while (oui != 0)
	{
		oui = loop(envn, oui, cmd);
	}
	i = ft_atoi_f(ft_getenv(envn, "?"));
	free_dptr(envn);
	write(1, "exit\n", 5);
	return (i);
}
