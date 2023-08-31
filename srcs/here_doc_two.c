/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:15:18 by sforesti          #+#    #+#             */
/*   Updated: 2023/08/31 14:20:17 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_size(int size, char *content)
{
	if (!content)
		size ++;
	else
		size += ft_strlen(content);
	return (size);
}

int	size_alloc(char *str, char **envp)
{
	int		i;
	int		size;
	char	*word;
	char	*content;

	i = 0;
	size = 0;
	content = NULL;
	while (str[i])
	{
		if (is_good_name_var(str, i))
		{
			word = dup_name_var(i, str, word);
			i += ft_strlen (word);
			content = ft_getenv(envp, word);
			size += count_size(size, content);
		}
		else if (str[i] != '\n' && str[i] != '\0')
			size ++;
		i ++;
	}
	if (word && word[0])
		free (word);
	return (size + 1);
}

int	add_var_env(char *var, char **envp, char *line)
{
	char	*content;
	int		i;
	int		y;

	y = 0;
	i = ft_strlen(line);
	content = ft_strmup(ft_getenv(envp, var));
	if (content == NULL)
	{
		line[i] = '\n';
		return (1);
	}
	while (content[y])
	{
		line[i] = content[y];
		i ++;
		y ++;
	}
	if (content && content[0])
		free (content);
	return (i);
}

int	is_good_name_var(char *str, int i)
{
	if (str[i] == '$' && ((str[i - 1] == 34 && str[i + 1] != 34)
		|| (str[i - 1] == 39 && str[i + 1] != 39) 
			|| (str[i - 1] != 34 && ft_isalnum(str[i + 1])) 
				|| (str[i - 1] != 39 && ft_isalnum(str[i + 1]))))
		return (1);
	return (0);
}