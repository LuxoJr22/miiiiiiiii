/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:29:31 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/05 13:25:26 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_input(char *limiter, char *str, char *line)
{
	while (1)
	{
		write (1, "> ", 2);
		line = get_next_line(0);
		if (!ft_strcmp(line, limiter))
			return (str);
		str = ft_strjoin_f(str, line, 3);
	}
}

int	add_var_env(char *var, char **envp, char *line)
{
	char	*content;
	int		i;
	int		y;

	y = 0;
	i = ft_strlen(line);
	content = ft_strmup(ft_getenv(envp, var));
	while (content[y])
	{
		line[i] = content[y];
		i ++;
		y ++;
	}
	return (i);
}

int	is_good_name_var(char *str, int i)
{
	if (str[i] == '$' && ((str[i - 1] == 34 && str[i + 1] != 34) ||
		(str[i - 1] == 39 && str[i + 1] != 39) ||
			(str[i - 1] != 34 && ft_isalnum(str[i + 1])) ||
				(str[i - 1] != 39 && ft_isalnum(str[i + 1]))))
		return (1);
	return (0);
}

int strlen_name_var(int i, char *str)
{
	int k;

	i ++;
	k = i;
	while (str[k] != ' ' && str[k] && str[k] != '\n' && str[k] != 34 && str[k] != 39)
		k ++;
	return (k);
}

char	*dup_name_var(int i, char *str, char *word)
{
	int k;

	i ++;
	k = i;
	while (str[k] != ' ' && str[k] && str[k] != '\n' && str[k] != 34 && str[k] != 39)
		k ++;
	word = malloc(sizeof(char) * (k + 1));
	k = 0;
	while (str[i] != ' ' && str[i] && str[i] != '\n' && str[i] != 34 && str[i] != 39)
	{
		word[k] = str[i];
		k ++;
		i ++;
	}
	word[k] = '\0';
	return (word);
}

int size_alloc(char *str, char **envp)
{
	int i;
	int size;
	char *word;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (is_good_name_var(str, i))
		{
			word = dup_name_var(i, str, word);
			i += ft_strlen (word);
			size += ft_strlen(ft_getenv(envp, word));
		}
		else if (str[i] != '\n' && str[i] != '\0')
			size ++;
		i ++;
	}
	return (size + 1);
}

char	*modif(char *str, char **envp)
{
	char	*line;
	char	*word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = malloc(sizeof(char) * size_alloc(str, envp));
	word = NULL;
	
	while (str[i])
	{
		if (is_good_name_var(str, i))
		{
			word = dup_name_var(i, str, word);
			i = strlen_name_var(i, str);
			j = add_var_env(word, envp, line);
			free (word);
		}
		line[j] = str[i];
		j ++;
		i ++;
	}
	//free (str);
	//free (line);
	return (line);
}

int	create_infile(char *limiter, char **envp)
{
	char	*line;
	char	*str;
	int		fd_hd[2];
	int		in_fd;

	str = ft_calloc(1, 1);
	limiter = ft_strjoin_f(limiter, ft_strdup("\n"), 3);
	line = NULL;
	if (pipe(fd_hd) == -1)
		perror("Minishell: HereDoc: ");
	str = read_input(limiter, str, line);
	free (line);
	str = ft_strjoin_f(str, ft_strdup("\0"), 3);
	line = modif(ft_strdup(str), envp);
	write (fd_hd[1], line, ft_strlen(line));
	free(str);
	free (line);
	free(limiter);
	in_fd = dup(fd_hd[0]);
	close(fd_hd[0]);
	close(fd_hd[1]);
	return (in_fd);
}
