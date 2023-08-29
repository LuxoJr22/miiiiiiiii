/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:25:01 by mboyer            #+#    #+#             */
/*   Updated: 2023/08/29 15:19:42 by sforesti         ###   ########.fr       */
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

void	get_command(t_cmd *cmd, char **envp, char *line)
{
	char	*command;
	int		stdin_me;
	int		stdout_me;
	int		boolean;

	command = NULL;
	if (cmd->arg[0] != NULL)
		command = str_lower(cmd->arg[0]);
	stdin_me = dup(STDIN_FILENO);
	stdout_me = dup(STDOUT_FILENO);
	if (cmd->in && cmd->in != -1)
		dup2(cmd->in, STDIN_FILENO);
	if (cmd->out && cmd->out != -1)
		dup2(cmd->out, STDOUT_FILENO);
	boolean = built_in(command, cmd, envp);
	dup2(stdin_me, 0);
	dup2(stdout_me, 1);
	if (!boolean)
	{
		exec_cmd(cmd, envp, line);
		if (!count_pipe(line) || command == NULL)
			waitpid(-1, NULL, 0);
	}
	free(command);
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
			if (str[i][0] == '$' && ret[0][0] == '?')
			{
				free(str[i]);
				str[i] = ft_strjoin_f((ft_itoa(g_glob)), ft_substr(ret[0], 1, ft_strlen(ret[0]) - 1), 3);
			}
			/*if (str[i][0] == '$' && (ret[0][0] > '0' && ret[0][0] < '9'))
			{
				if (argc >= ret[0][0] - 48)
					str[i] = ft_strjoin((ft_substr(argv[ret[0][0] - 48])), ft_substr(ret[0], 1, ft_strlen(ret[0]) - 1));
			}*/
			else if (str[i][0] == '$')
			{
				free(str[i]);
				str[i] = ft_getenv(envp, ret[0]);
			}
			else
			{
				free(str[i]);
				str[i] = ft_strmup(ret[0]);
			}
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

int	main(int ac, char **av, char **envp)
{
	char		*oui;
	t_cmd		*cmd;
	char		**envn;
	int			i;

	(void) ac;
	(void) av;
	i = -1;
	envn = malloc(sizeof(char *) * size_dptr(envp) + 1);
	while (envp[++i])
		envn[i] = ft_strdup(envp[i]);
	envn[i + 1] = 0;
	cmd = NULL;
	oui = getcwd(NULL, 0);
	signal(SIGINT, interrupt);
	while (oui != 0)
	{
		//g_glob = errno;
		free(oui);
		oui = readline("Minishell>");
		if (oui && *oui)
		{
			add_history(oui);
			cmd = parsed_line(oui, envn);
			manage_exec(oui, envn, cmd);
			//free_list(cmd);
			//free(oui);
		}
	}
	return (0);
}
