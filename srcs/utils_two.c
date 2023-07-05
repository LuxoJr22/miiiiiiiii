/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:59:54 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/05 10:09:01 by sforesti         ###   ########.fr       */
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
			ret = ft_strjoin_f(ft_strjoin_f(ret, str[len], 4), " ", 4);
		len ++;
	}
	return (ret);
}

int	size_dptr(char **str)
{
	int	i;

	i = -1;
	while (str[i])
		i++;
	return (i);
}
