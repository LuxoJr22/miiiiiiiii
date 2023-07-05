/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxojr <luxojr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:29:31 by sforesti          #+#    #+#             */
/*   Updated: 2023/07/05 13:25:26 by luxojr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_input(char *limiter, char *str, char *line)
{
	while (1)
	{
		write (1, "> ", 2);
		line = get_next_line(0);
		if (!ft_strcmp(line, limiter))
			return (str);
		str = ft_strjoin_f(str, line, 3);
	}
}

int	create_infile(char *limiter)
{
	char	*line;
	char	*str;
	int		fd_hd[2];
	int		in_fd;

	str = ft_calloc(1, 1);
	limiter = ft_strjoin_f(limiter, ft_strdup("\n"), 3);
	line = NULL;
	if (pipe(fd_hd) == -1)
		perror("Minishell: HereDoc: ");
	str = read_input(limiter, str, line);
	free (line);
	str = ft_strjoin_f(str, ft_strdup("\0"), 3);
	write (fd_hd[1], str, ft_strlen(str));
	free(str);
	free(limiter);
	in_fd = dup(fd_hd[0]);
	close(fd_hd[0]);
	close(fd_hd[1]);
	return (in_fd);
}
