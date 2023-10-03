/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:01:47 by sforesti          #+#    #+#             */
/*   Updated: 2023/10/03 18:50:26 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_charset_pa(char const s, int mode)
{
	if (mode == 1)
	{
		if (s == '|')
			return (1);
	}
	if (mode == 2)
	{
		if (s == ' ' || s == '\t')
			return (1);
	}
	return (0);
}

int	ft_size_strs(char const *s, int mode)
{
	int	i;
	int	j;
	int	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (s[i])
	{
		while (ft_is_charset_pa(s[i], mode) && s[i])
			i ++;
		if (!ft_is_charset_pa(s[i], mode) && s[i])
		{
			j ++;
			while ((!ft_is_charset_pa(s[i], mode) || quote) && s[i])
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

	(void) c;
	quote = 0;
	nb_q = nb_quotes(s, start, end);
	if (nb_q % 2 == 1)
		nb_q -= 1;
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (0);
	i = 0;
	while (start < end)
	{
		if ((((s[start] == 34 || s[start] == 39) && !quote)
				|| quote == s[start]) && (c != 1 && c != 2))
			start++;
		else
			str[i++] = s[start++];
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split_parse(char const *s, int mode)
{
	char	**r_str;
	int		i;
	int		verif;

	i = 0;
	verif = 0;
	if (!s)
		return (0);
	r_str = malloc(sizeof(char *) * (ft_size_strs(s, mode) + 1));
	if (!r_str)
		return (0);
	while (mode == 1 && s[i] == '|')
		i++;
	while (mode == 2 && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (!s[i])
		verif = 1;
	r_str = ft_fill_pa(s, mode, r_str, verif);
	return (r_str);
}
