/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_champion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 02:16:52 by mbakhti           #+#    #+#             */
/*   Updated: 2019/04/01 10:57:13 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int			create_file(char *filename)
{
	int		fd;

	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		ft_exit_error("error: can't create the binary file");
	return (fd);
}

static void			get_output_name(char *filename, char **output)
{
	filename[ft_strlen(filename) - 2] = '\0';
	if (!(*output = ft_strjoin(filename, ".cor")))
	filename[ft_strlen(filename)] = '.';
}

void				compile_champion(t_bytecode champion, char *filename)
{
	char	*output;
	int		fd;
	int		size;

	get_output_name(filename, &output);
	fd = create_file(output);
	ft_printf("Writing output program to %s\n", output);
	size = champion.header.prog_size;
	champion.header.magic = convert_endian32(champion.header.magic);
	champion.header.prog_size = convert_endian32(champion.header.prog_size);
	write(fd, &champion.header, sizeof(champion.header));
	write(fd, champion.program, size);
	ft_strdel(&output);
	ft_strdel(&champion.program);
	close(fd);
}
