/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 19:25:08 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/28 18:43:56 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*result;
	t_list	*new_content;

	result = ft_memalloc(sizeof(t_list));
	if (result == NULL)
	{
		return (NULL);
	}
	result->content = (void*)content;
	if (content == NULL)
	{
		result->content_size = 0;
		result->content = NULL;
	}
	else
	{
		new_content = ft_memalloc(content_size);
		if (new_content == NULL)
			return (NULL);
		ft_memcpy(new_content, content, content_size);
		result->content = new_content;
		result->content_size = content_size;
	}
	result->next = NULL;
	return (result);
}
