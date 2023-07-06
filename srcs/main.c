/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:25:01 by mboyer            #+#    #+#             */
/*   Updated: 2023/07/06 15:26:04 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_command(t_cmd *cmd, char **envp, char *line)
{
	char	*command;

	command = NULL;
	if (cmd->arg[0] != NULL)
		command = str_lower(cmd->arg[0]);
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
	{
		exec_cmd(cmd, envp, line);
		if (!count_pipe(line) || command == NULL)
			waitpid(-1, NULL, 0);
	}
}

char	*ft_strmup(const char *s1)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	if (!s1)
	{
		ret = malloc(sizeof(char));
		ret[0] = '\0';
		return (ret);
	}
	len = ft_strlen(s1);
	ret = malloc(sizeof(char) * len + 1);
	if (ret == 0)
		return (0);
	while (i < len)
	{
		ret[i] = s1[i];
		i ++;
	}
	ret[i] = '\0';
	return (ret);
}

int	is_in_quote(char *str, char c)
{
	int	i;
	int	it;
	int	quote;

	i = 0;
	it = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		if (str[i] == c && quote != 39)
			it ++;
		i ++;
	}
	return (it);
}

char	**pre_process(char **str, char **envp, char **argv)
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
			if (str[i][0] == '$' && ret[0][0] == '?')
				str[i] = ft_strjoin((ft_itoa(g_glob)), ft_substr(ret[0], 1, ft_strlen(ret[0]) - 1));
			if (str[i][0] == '$' && (ret[0][0] > '0' && ret[0][0] < '9'))
			{
				if (argc >= ret[0][0] - 48)
					str[i] = ft_strjoin((ft_substr(argv[ret[0][0] - 48])), ft_substr(ret[0], 1, ft_strlen(ret[0]) - 1));
			}
			else if (str[i][0] == '$')
				str[i] = ft_strmup(ft_getenv(envp, ret[0]));
			else
				str[i] = ft_strmup(ret[0]);
			while (ret[y++])
				str[i] = ft_strjoin_f(str[i], ft_getenv(envp, ret[y]), 1);
			y = 1;
		}
		else
			str[i] = reset_quote(str[i]);
	}
	return (str);
}

int	main(int ac, char **av, char **envp)
{
	char		*oui;
	t_cmd		*cmd;

	(void) ac;
	(void) av;
	cmd = NULL;
	oui = getcwd(NULL, 0);
	signal(SIGINT, interrupt);
	signal(SIGQUIT, quit);
	while (oui != 0)
	{
		g_glob = errno;
		oui = readline("Minishell>");
		if (oui && *oui)
		{
			add_history(oui);
			cmd = parsed_line(oui, envp);
			manage_exec(oui, envp, cmd);
			//free_list(cmd);
			//free(oui);
		}
	}
	return (0);
}
