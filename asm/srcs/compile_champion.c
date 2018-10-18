/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_champion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 02:16:52 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/07 15:50:36 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_uint(int fd, unsigned int number)
{
	char	buffer[4];

	buffer[0] = (number & 0xff000000) >> 24;
	buffer[1] = (number & 0x00ff0000) >> 16;
	buffer[2] = (number & 0x0000ff00) >> 8;
	buffer[3] = (number & 0x000000ff);
	write(fd, buffer, sizeof(buffer));
}

static void	write_header(int fd, t_header header)
{
	write_uint(fd, header.magic);
	write(fd, header.prog_name, PROG_NAME_LENGTH);
	write_uint(fd, 0);
	write_uint(fd, header.prog_size);
	write(fd, header.comment, COMMENT_LENGTH);
	write_uint(fd, 0);
}

static int	create_file(char *filename)
{
	int		fd;

	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		ft_exit_error("error: can't create the binary file");
	return (fd);
}

static void	get_output_name(char *filename, char **output)
{
	filename[ft_strlen(filename) - 2] = '\0';
	if (!(*output = ft_strjoin(filename, ".cor")))
		ft_exit_error("error: can't malloc");
	filename[ft_strlen(filename)] = '.';
}

void		compile_champion(t_bytecode champion, char *filename)
{
	char	*output;
	int		fd;

	get_output_name(filename, &output);
	fd = create_file(output);
	ft_printf("Writing output program to %s\n", output);
	write_header(fd, champion.header);
	write(fd, champion.program, champion.header.prog_size);
	ft_strdel(&output);
	ft_strdel(&champion.program);
	close(fd);
}
