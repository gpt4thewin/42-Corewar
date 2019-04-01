/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:31:14 by mbakhti           #+#    #+#             */
/*   Updated: 2019/04/01 13:58:27 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	parse_comment(char *comment, char *string)
{
	int		size;

	size = ft_strlen(string) - 2;
	if (size > COMMENT_LENGTH)
	{
		ft_fprintf(2, "Champion comment too long (Max length %d)\n",
		COMMENT_LENGTH);
		exit(EXIT_FAILURE);
	}
	ft_strncpy(comment, &string[1], size);
}

static void	parse_name(char *prog_name, char *string)
{
	int		size;

	size = ft_strlen(string) - 2;
	if (size > PROG_NAME_LENGTH)
	{
		ft_fprintf(2, "Champion name too long (Max length %d)\n",
		PROG_NAME_LENGTH);
		exit(EXIT_FAILURE);
	}
	ft_strncpy(prog_name, &string[1], size);
}

static void	parse_commands(t_token **current, t_header *header)
{
	char	*command;

	if ((*current)->type != COMMAND)
		syntax_error(**current);
	command = (*current)->value;
	*current = (*current)->next;
	if ((*current)->type != STRING)
		syntax_error(**current);
	if (ft_strequ(command, NAME_CMD_STRING))
		parse_name(header->prog_name, (*current)->value);
	else
		parse_comment(header->comment, (*current)->value);
	*current = (*current)->next;
}

static void	get_next_token(t_token **current)
{
	while ((*current)->type == ENDLINE || (*current)->type == COMMENT)
		*current = (*current)->next;
}

void		generate_header(t_header *header, t_token **current)
{
	get_next_token(current);
	parse_commands(current, header);
	get_next_token(current);
	parse_commands(current, header);
	get_next_token(current);
	if ((*current)->type == END)
		syntax_error(**current);
}
