/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:18:53 by sforesti          #+#    #+#             */
/*   Updated: 2023/10/03 15:27:31 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*r_str;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	else if (ft_strlen(s) < len)
		r_str = malloc(sizeof(char) * (ft_strlen(s) - start) + 1);
	else
		r_str = malloc(sizeof(char) * len + 1);
	if (!r_str)
		return (NULL);
	while (len-- && s[start])
		r_str[i++] = s[start++];
	r_str[i] = '\0';
	return (r_str);
}
