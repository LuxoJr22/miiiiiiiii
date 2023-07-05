/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:01:47 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/05 02:39:51 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_charset_two(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	size_strs_two(char const *s, char *c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (is_charset_two(s[i], c) && s[i])
			i ++;
		if (!is_charset_two(s[i], c) && s[i])
		{
			j ++;
			while (!is_charset_two(s[i], c) && s[i])
				i++;
		}
	}
	return (j);
}

char	*fill_str_two(char const *s, int start, int end)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (0);
	i = 0;
	while (start < end)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

char	**fill_two(char const *s, char *c, char **r_str, int verif)
{
	int	i;
	int	j;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	j = 0;
	while (s[i] && !verif)
	{
		while (s[i] && is_charset_two(s[i], c))
			i++;
		start = i;
		while (s[i] && !is_charset_two(s[i], c))
			i++;
		end = i;
		while (s[i] && is_charset_two(s[i], c))
			i++;
		r_str[j] = fill_str_two(s, start, end);
		j ++;
	}
	r_str[j] = 0;
	return (r_str);
}

char	**ft_split_two(char *s, char *c)
{
	char	**r_str;
	int		i;
	int		verif;

	i = 0;
	verif = 0;
	if (!s)
		return (0);
	r_str = malloc(sizeof(char *) * (size_strs_two(s, c) + 1));
	if (!r_str)
		return (0);
	while (is_charset_two(s[i], c))
		i++;
	if (!s[i])
		verif = 1;
	r_str = fill_two(s, c, r_str, verif);
	return (r_str);
}
