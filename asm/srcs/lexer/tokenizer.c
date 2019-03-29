/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 23:14:03 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/28 18:44:19 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_func	g_is_token_func[] =
{
	{&is_endline, ENDLINE},
	{&is_separator, SEPARATOR},
	{&is_comment, COMMENT},
	{&is_command, COMMAND},
	{&is_string, STRING},
	{&is_label, LABEL},
	{&is_register, REGISTER},
	{&is_indirect, INDIRECT},
	{&is_indirect_label, INDIRECT_LABEL},
	{&is_direct, DIRECT},
	{&is_direct_label, DIRECT_LABEL},
	{&is_instruction, INSTRUCTION},
	{NULL, END}
};

static void	tokenize(t_token new, t_token **last)
{
	(*last)->type = new.type;
	(*last)->value = ft_strdup(new.value);
	(*last)->next = ft_memalloc(sizeof(t_token));
	(*last) = (*last)->next;
	(*last)->type = END;
	(*last)->value = NULL;
	(*last)->next = NULL;
}

_Bool		tokenized(char *tok, char next, t_token **last)
{
	int		i;
	t_token	new;

	i = 0;
	while (g_is_token_func[i].token_type != END)
	{
		if (g_is_token_func[i].ptrfunc(tok, next, (*last)->position))
		{
			new.type = g_is_token_func[i].token_type;
			new.value = tok;
			tokenize(new, last);
			return (true);
		}
		i++;
	}
	return (false);
}
