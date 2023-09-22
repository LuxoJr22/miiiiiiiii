/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_second.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:36:16 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/22 16:10:09 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dptr(char **dptr)
{
	int	i;

	i = -1;
	while (dptr[++i])
		free(dptr[i]);
	free(dptr);
}

char	*free_dptr_line(char **dptr, char *str)
{
	char	*ret;

	ret = ft_strdup(str);
	free_dptr(dptr);
	return (ret);
}

void	reset_quote_two(int quote, char *str, char	*ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!quote && (str[i] == 34 || str[i] == 39))
			quote = str[i++];
		else if (quote == str[i])
		{
			quote = 0;
			i ++;
		}
		else if (str[i])
		{
			ret[j] = str[i];
			i ++;
			j ++;
		}
	}
	ret[j] = 0;
	free(str);
}

char	*reset_quote(char *str)
{
	int		i;
	int		j;
	int		quote;
	char	*ret;

	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == 34 || str[i] == 39))
		{
			quote = str[i];
			j ++;
		}
		else if (quote == str[i])
		{
			quote = 0;
			j ++;
		}
		i ++;
	}
	ret = malloc(sizeof(char) * (i - j) + 1);
	reset_quote_two(quote, str, ret);
	return (ret);
}

char	*get_line_env(char *str, char *ret, char **envp)
{
	if (str[0] == '$')
	{
		free(str);
		str = ft_getenv(envp, ret);
		if (!str)
			str = ft_strdup("");
	}
	else
	{
		free(str);
		str = ft_strmup(ret);
	}
	return (str);
}
