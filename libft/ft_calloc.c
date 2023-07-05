/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:27:50 by sforesti          #+#    #+#             */
/*   Updated: 2023/06/23 17:10:15 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pt;

	if (nmemb == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	pt = malloc(nmemb * size);
	if (!pt)
		return (NULL);
	ft_bzero(pt, nmemb * size);
	return (pt);
}
