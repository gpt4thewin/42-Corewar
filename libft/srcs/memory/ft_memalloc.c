/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 18:29:07 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/28 18:41:26 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ft_safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		ft_printf("COREWAR: ERROR MALLOC\n");
		exit(EXIT_FAILURE);
	}
}

void	*ft_memalloc(size_t size)
{
	void	*ptr;

	ptr = ft_safe_malloc(size);
	if (ptr != NULL)
	{
		ft_bzero(ptr, size);
		return (ptr);
	}
	return (NULL);
}
