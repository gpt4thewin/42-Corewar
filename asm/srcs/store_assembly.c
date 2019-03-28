/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_assembly.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 21:30:19 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/28 18:43:58 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	concat_line(char **instructions, char *line)
{
	int		size;

	size = ft_strlen(*instructions) + ft_strlen(line) + 2;
	if (!(*instructions = realloc(*instructions, sizeof(char) * size)))
		ft_exit_error("error: can't realloc");
	ft_strcat(ft_strcat(*instructions, line), "\n");
}

static int	open_sourcefile(char *filename)
{
	int		fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_exit_error("error: can't open sourcefile");
	return (fd);
}

void		store_assembly(char **instructions, char *filename)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open_sourcefile(filename);
	if (!(*instructions = ft_strnew(0)))
		ft_exit_error("error: can't ft_memalloc");
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret < 0)
			ft_exit_error("error: can't read sourcefile");
		concat_line(instructions, line);
		ft_strdel(&line);
	}
	close(fd);
}
