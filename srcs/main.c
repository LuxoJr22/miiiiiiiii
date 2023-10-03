/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:25:01 by mboyer            #+#    #+#             */
/*   Updated: 2023/10/03 18:42:01 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_pid;

int	built_in(char *command, t_cmd *cmd, char **envp, char *line)
{
	if (!cmd->here_doc && is_equal("echo", command))
		ft_echo(cmd->arg);
	else if (!cmd->here_doc && is_equal("pwd", command))
		ft_pwd(envp);
	else if (!cmd->here_doc && is_equal("env", command) && !cmd->arg[1])
		ft_env(envp);
	else if (!cmd->here_doc && is_equal("exit", command))
		ft_exit(envp, cmd->arg);
	else if (!cmd->here_doc && is_equal("cd", command))
		ft_cd(cmd->arg[1], envp);
	else if (!cmd->here_doc && is_equal("./minishell", command))
		exec_minishell(command, envp, cmd, line);
	else
		return (0);
	return (1);
}

char	**pre_process(t_cmd *cmd, char **envp)
{
	int		i;
	char	**ret;
	char	**str;

	str = cmd->arg;
	i = -1;
	while (str[++i])
	{
		if (is_in_quote(str[i], '$'))
		{
			str[i] = reset_quote(str[i]);
			ret = ft_split(str[i], '$');
			str[i] = process_line(str[i], ret, envp);
		}
		else
			str[i] = reset_quote(str[i]);
	}
	process_redirect(envp, cmd);
	return (NULL);
}

char	**init_env(char **envp)
{
	char	**envn;
	int		i;
	int		lvl;

	i = -1;
	if (!size_dptr(envp))
	{
		envn = malloc(sizeof(char *) * (5));
		envn[0] = ft_strjoin_f("PWD=", getcwd(NULL, 0), 4);
		envn[1] = ft_strdup("SHLVL=1");
		envn[2] = ft_strdup("_=/usr/bin/env");
		i = 3;
	}
	else
	{
		lvl = ft_atoi_f(ft_getenv(envp, "SHLVL"));
		envn = malloc(sizeof(char *) * (size_dptr(envp) + 2));
		i = fill_envp(envn, envp, i, lvl);
	}
	envn[i] = ft_strdup("?=0");
	envn[i + 1] = 0;
	return (envn);
}

char	**loop(char **envn, char *oui, t_cmd *cmd)
{
	if (g_pid == -2)
		change_env(envn, "?=131");
	if (g_pid == -3)
		change_env(envn, "?=1");
	if (g_pid == -4 || g_pid == -5)
		change_env(envn, "?=130");
	if (oui && *oui)
	{
		add_history(oui);
		cmd = parsed_line(oui, envn);
		if (cmd && cmd->name && ((!ft_strcmp(cmd->name, "export")
					&& ft_strlen(cmd->name) == 6)
				|| (!ft_strcmp(cmd->name, "unset")
					&& ft_strlen(cmd->name) == 5)))
			envn = env_change(envn, cmd);
		else if (cmd)
			manage_exec(oui, envn, cmd);
		free_list(cmd);
	}
	else
		change_env(envn, "?=0");
	return (envn);
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
		free(oui);
		oui = readline("Minishell>");
		envn = loop(envn, oui, cmd);
	}
	i = ft_atoi_f(ft_getenv(envn, "?"));
	free_dptr(envn);
	write(1, "exit\n", 5);
	return (i);
}
