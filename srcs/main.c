/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:25:01 by mboyer            #+#    #+#             */
/*   Updated: 2023/09/11 12:51:50 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in(char *command, t_cmd *cmd, char **envp)
{
	if (is_equal("echo", command))
		ft_echo(cmd->arg);
	else if (is_equal("pwd", command))
		ft_pwd(envp);
	else if (is_equal("export", command))
		ft_export(envp, cmd->arg);
	else if (is_equal("env", command) && !cmd->arg[1])
		ft_env(envp);
	else if (is_equal("exit", command))
		ft_exit(envp, cmd->arg[1]);
	else if (is_equal("unset", command))
		ft_unset(cmd->arg, envp);
	else if (is_equal("cd", command))
		ft_cd(cmd->arg[1], envp);
	else
		return (0);
	return (1);
}

char	*get_line_env(char *str, char *ret, char **envp)
{
	if (str[0] == '$' && ret[0] == '?')
	{
		free(str);
		str = ft_strjoin_f((ft_itoa(errno)),
				ft_substr(ret, 1, ft_strlen(ret) - 1), 3);
	}
	else if (str[0] == '$')
	{
		free(str);
		str = ft_getenv(envp, ret);
	}
	else
	{
		free(str);
		str = ft_strmup(ret);
	}
	return (str);
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
	envn = malloc(sizeof(char *) * size_dptr(envp) + 1);
	while (envp[++i])
		envn[i] = ft_strdup(envp[i]);
	envn[i + 1] = 0;
	return (envn);
}

int	main(int ac, char **av, char **envp)
{
	char		*oui;
	t_cmd		*cmd;
	char		**envn;

	(void) ac;
	(void) av;
	g_pid = -1;
	ft_init_signals();
	envn = init_env(envp);
	cmd = NULL;
	oui = getcwd(NULL, 0);
	while (oui != 0)
	{
		free(oui);
		oui = readline("Minishell>");
		if (oui && *oui)
		{
			add_history(oui);
			cmd = parsed_line(oui, envn);
			manage_exec(oui, envn, cmd);
			free_list(cmd);
		}
	}
	free_dptr(envn);
	write(1, "exit\n", 5);
	return (0);
}
