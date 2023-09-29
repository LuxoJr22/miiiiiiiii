/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:24:07 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/29 18:30:47 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in(char *str, char c)
{
	int	i;
	int	it;

	i = 0;
	it = 0;
	while (str[i])
	{
		if (str[i] == c)
			it ++;
		i ++;
	}
	return (it);
}

int	is_equal(char *search, char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (search[i])
	{
		if (str[i] != search[i])
			return (0);
		i ++;
	}
	if (str[i])
		return (0);
	return (1);
}

char	*ft_quote(char *str)
{
	int		i;
	int		off;
	char	*ret;

	off = 0;
	i = 0;
	while (str[i])
		i ++;
	ret = malloc(sizeof(char) * (i + 3));
	i = 0;
	while (str[i])
	{
		ret[i + off] = str[i];
		if (str[i] == '=' && off == 0)
		{
			off ++;
			ret[i + off] = '"';
		}
		i ++;
	}
	if (off > 0)
		ret[i + off++] = '"';
	ret[i + off] = '\0';
	return (ret);
}

int	is_strnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i ++;
	}
	return (1);
}

char	*str_lower(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i])
		i ++;
	ret = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i])
	{
		ret[i] = ft_tolower(str[i]);
		i ++;
	}
	ret[i] = '\0';
	return (ret);
}
