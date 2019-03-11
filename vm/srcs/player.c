/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:22:34 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/11 17:18:57 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	read_error(const char *filename)
{
	ft_fprintf(2, "%s is not a corewar executable\n", filename);
	exit(EXIT_FAILURE);
}

static void	read_or_die(int fd, void *ptr, size_t size, const char *filename)
{
	size_t		read_size;

	read_size = read(fd, ptr, size);
	if (read_size != size)
	{
		read_error(filename);
	}
}

void		player_load(t_player *player)
{
	int			fd;
	t_header	header;

	fd = (int)fopen(player->file, "rb");
	if (fd == 0)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	read_or_die(fd, &header, sizeof(header), player->file);
	if (header.magic != COREWAR_EXEC_MAGIC || header.prog_size > CHAMP_MAX_SIZE)
		read_error(player->file);
	read_or_die(fd, &player->program, header.prog_size, player->file);
	close(fd);
}
