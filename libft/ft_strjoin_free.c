/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:54:55 by sforesti          #+#    #+#             */
/*   Updated: 2023/04/24 15:29:00 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_f(char *s1, char *s2, int mode)
{
	char	*r_str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	r_str = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!r_str)
		return (NULL);
	j = -1;
	i = -1;
	while (s1[++i])
		r_str[i] = s1[i];
	while (s2[++j])
		r_str[i++] = s2[j];
	r_str[i] = '\0';
	if (mode == 1 || mode == 3)
		free(s1);
	if (mode == 2 || mode == 3)
		free(s2);
	return (r_str);
}
