/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_magic_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:24:51 by aweaver           #+#    #+#             */
/*   Updated: 2022/06/20 14:53:01 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_magic_malloc(void *(*funct)(size_t), size_t size, void *addr)
{
	static t_mlc	malloc_list;
	void			*tmp;

	if (funct == free)
	{
		printf("free utilisé");
	}
	else
	{
		tmp = malloc(size);
	}
	return (tmp);
}
