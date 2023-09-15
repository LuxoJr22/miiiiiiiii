/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:59:54 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/15 16:17:59 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_union(char	**str)
{
	int		len;
	char	*ret;

	len = 0;
	ret = ft_strdup("");
	while (str[len])
	{
		if (is_in(str[len], '<') || is_in(str[len], '>'))
		{
			if ((int)ft_strlen(str[len]) == is_in(str[len], '<')
				|| (int)ft_strlen(str[len]) == is_in(str[len], '>'))
				len ++;
		}
		else
			ret = ft_strjoin_f(ft_strjoin_f(ret, str[len], 1), " ", 1);
		len ++;
	}
	return (ret);
}

void	free_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_file	*tp;

	tmp = NULL;
	tp = NULL;
	while (cmd)
	{
		tmp = cmd->next;
		while (cmd->file)
		{
			tp = cmd->file->next;
			if (cmd->file->fd_file && cmd->file->fd_file[0] != '\0')
				free(cmd->file->fd_file);
			free(cmd->file);
			cmd->file = tp;
		}
		if (cmd->arg)
			free_dptr(cmd->arg);
		if (cmd->name && cmd->name[0])
			free(cmd->name);
		free(cmd);
		cmd = tmp;
	}
}

int	size_dptr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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
		if (str[i] == c && quote != 39
			&& str[i + 1] != 34 && (ft_isalpha(str[i + 1])
				|| str[i + 1] == '_'
				|| str[i + 1] == '?'))
			it ++;
		i ++;
	}
	return (it);
}
