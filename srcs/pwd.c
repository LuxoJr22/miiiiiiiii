/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:54:40 by sforesti          #+#    #+#             */
/*   Updated: 2023/09/13 19:03:40 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **envp)
{
	char	*ret;

	ret = ft_getenv(envp, "PWD");
	printf("%s\n", ret);
	free(ret);
}

int	ft_atoi_f(char *str)
{
	int	i;
	int	negative;
	int	nb;

	i = 0;
	negative = 1;
	nb = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i ++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -1;
		i ++;
	}
	while (48 <= str[i] && str[i] <= 57 && str[i])
	{
		nb *= 10;
		nb += (str[i] - 48);
		i ++;
	}
	free(str);
	return (nb * negative);
}
