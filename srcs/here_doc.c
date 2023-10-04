/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:29:31 by sforesti          #+#    #+#             */
/*   Updated: 2023/10/04 13:04:37 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_input(char *limiter, char *line)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (0);
	g_pid = fork();
	if (g_pid == 0)
	{
		while (1)
		{
			write (1, "> ", 2);
			line = get_next_line(0);
			verif_limiter(line, limiter);
			write(fd[1], line, ft_strlen(line));
			free (line);
		}
	}
	else
	{
		waitpid(g_pid, NULL, 0);
		if (g_pid == -3)
			return (0);
		close (fd[1]);
		return (fd_to_str(fd));
	}
	return (fd_to_str(fd));
}

int	strlen_name_var(int i, char *str)
{
	int	k;

	i ++;
	k = i;
	while (str[k] != ' ' && str[k]
		&& str[k] != '\n' && str[k] != 34 && str[k] != 39)
		k ++;
	return (k);
}

char	*dup_name_var(int i, char *str, char *word)
{
	int	k;

	i ++;
	k = i;
	while (str[k] != ' ' && str[k]
		&& str[k] != '\n' && str[k] != 34 && str[k] != 39)
		k ++;
	word = malloc(sizeof(char) * (k + 1));
	k = 0;
	while (str[i] != ' ' && str[i]
		&& str[i] != '\n' && str[i] != 34 && str[i] != 39)
	{
		word[k] = str[i];
		k ++;
		i ++;
	}
	word[k] = '\0';
	return (word);
}

char	*modif(char *str, char **envp)
{
	char	*line;
	char	*word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = ft_calloc(size_alloc(str, envp), sizeof(char));
	word = NULL;
	while (str[i])
	{
		if (is_good_name_var(str, i))
		{
			word = dup_name_var(i, str, word);
			i = strlen_name_var(i, str);
			j = add_var_env(word, envp, line);
			if (word[0])
				free(word);
		}
		line[j++] = str[i++];
	}
	line[j] = '\0';
	free (str);
	return (line);
}

int	create_infile(char *limiter, char **envp)
{
	char	*line;
	char	*str;
	int		fd_hd[2];
	int		in_fd;

	str = NULL;
	limiter = ft_strjoin_f(limiter, ft_strdup("\n"), 2);
	line = NULL;
	signal(SIGQUIT, fonction);
	if (pipe(fd_hd) == -1)
		perror("Minishell: HereDoc: ");
	str = read_input(limiter, line);
	str = ft_strjoin_f(str, "\0", 1);
	if (str)
		line = modif(ft_strdup(str), envp);
	write (fd_hd[1], line, ft_strlen(line));
	free(str);
	free (line);
	free (limiter);
	in_fd = dup(fd_hd[0]);
	close(fd_hd[0]);
	close(fd_hd[1]);
	signal(SIGQUIT, ft_handle_ctrl_slash);
	return (in_fd);
}
