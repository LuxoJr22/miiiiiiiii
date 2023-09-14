/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:01:47 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/14 15:17:21 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_charset_pa(char const s, char c)
{
	return (c == s);
}

int	ft_size_strs(char const *s, char c)
{
	int	i;
	int	j;
	int	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (s[i])
	{
		while (ft_is_charset_pa(s[i], c) && s[i])
			i ++;
		if (!ft_is_charset_pa(s[i], c) && s[i])
		{
			j ++;
			while ((!ft_is_charset_pa(s[i], c) || quote) && s[i])
			{
				if ((s[i] == 39 || s[i] == 34) && quote == 0)
					quote = s[i];
				else if (s[i] == quote)
					quote = 0;
				i++;
			}
		}
	}
	return (j);
}

int	nb_quotes(char const *s, int start, int end)
{
	int	quote;
	int	nb;

	nb = 0;
	quote = 0;
	while (start < end)
	{
		if (((s[start] == 34 || s[start] == 39) && !quote) || quote == s[start])
		{
			quote = s[start];
			nb ++;
		}
		start++;
	}
	return (nb);
}

char	*ft_fill_str_pa(char const *s, int start, int end, char c)
{
	char	*str;
	int		i;
	int		nb_q;
	int		quote;

	quote = 0;
	nb_q = nb_quotes(s, start, end);
	if (nb_q % 2 == 1)
		nb_q -= 1;
	str = malloc(sizeof(char) * (end - start + 2 - nb_q));
	if (!str)
		return (0);
	i = 0;
	while (start < end)
	{
		if ((((s[start] == 34 || s[start] == 39) && !quote)
				|| quote == s[start]) && (c != '|' && c != ' '))
			start++;
		else
			str[i++] = s[start++];
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split_parse(char const *s, char c)
{
	char	**r_str;
	int		i;
	int		verif;

	i = 0;
	verif = 0;
	if (!s)
		return (0);
	r_str = malloc(sizeof(char *) * (ft_size_strs(s, c) + 1));
	if (!r_str)
		return (0);
	while (s[i] == c)
		i++;
	if (!s[i])
		verif = 1;
	r_str = ft_fill_pa(s, c, r_str, verif);
	return (r_str);
}
