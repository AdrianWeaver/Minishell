/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_magic_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@42.fr>                     +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:24:51 by aweaver           #+#    #+#             */
/*   Updated: 2022/06/23 17:20:46 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_magic_malloc(int funct, size_t size, void *addr)
{
	static t_mlc	*head;
	t_mlc			*list_elem;

	if (funct == FLUSH)
		ft_free_mlc_and_quit(head);
	else if (funct == FREE)
		ft_cleanly_delone_mlc(&head, addr);
	else if (funct == MALLOC || funct == ADD)
	{
		list_elem = malloc(sizeof(*list_elem) * 1);
		if (list_elem == NULL)
			ft_free_mlc_and_quit(head);
		if (funct == MALLOC)
		{
			list_elem->addr = malloc(size);
			if (list_elem->addr == NULL && size != 0)
				ft_free_mlc_and_quit(head);
		}
		if (funct == ADD)
			list_elem->addr = addr;
		head = ft_malloc_list_add_back(&head, list_elem);
		return (list_elem->addr);
	}
	return (NULL);
}
