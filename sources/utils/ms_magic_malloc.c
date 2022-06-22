/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_magic_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:24:51 by aweaver           #+#    #+#             */
/*   Updated: 2022/06/21 16:41:01 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_magic_malloc(int funct, size_t size, void *addr)
{
	static t_mlc	*head;
	t_mlc			*list_elem;

	if (funct == FLUSH)
	{
		ft_free_mlc_and_quit(head);
		return (NULL);
	}
	else if (funct == FREE)
	{
		ft_cleanly_delone_mlc(&head, addr);
		return (NULL);
	}
	else if (funct == MALLOC)
	{
		list_elem = malloc(sizeof(*list_elem) * 1);
		if (list_elem == NULL)
			ft_free_mlc_and_quit(head);
		list_elem->addr = malloc(size);
		if (list_elem->addr == NULL && size != 0)
			ft_free_mlc_and_quit(head);
		head = ft_malloc_list_add_back(&head, list_elem);
		return (list_elem->addr);
	}
	return (NULL);
}
