/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_parse_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:45:36 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/05 03:14:55 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fill_two(int quote, char const *s, char c, int i)
{
	while (s[i] && (!ft_is_charset_pa(s[i], c) || quote))
	{
		if ((s[i] == 39 || s[i] == 34) && quote == 0)
			quote = s[i];
		else if (s[i] == quote)
			quote = 0;
		i++;
	}
	return (i);
}

char	**ft_fill_pa(char const *s, char c, char **r_str, int verif)
{
	int	i;
	int	j;
	int	start;
	int	quote;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	j = 0;
	quote = 0;
	while (s[i] && !verif)
	{
		while (s[i] && ft_is_charset_pa(s[i], c))
			i++;
		start = i;
		end = ft_fill_two(quote, s, c, i);
		i = end;
		while (s[i] && ft_is_charset_pa(s[i], c))
			i++;
		r_str[j] = ft_fill_str_pa(s, start, end, c);
		j ++;
	}
	r_str[j] = 0;
	return (r_str);
}
