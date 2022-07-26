/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_magic_malloc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@42.fr>                     +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:40:03 by aweaver           #+#    #+#             */
/*   Updated: 2022/07/26 17:03:25 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delone_mlc(t_mlc *mlc, void (*del)(void *))
{
	if (!mlc)
		return ;
	del(mlc->addr);
	mlc->addr = NULL;
	del(mlc);
	mlc = NULL;
}

void	ft_free_mlc_and_quit(t_mlc *mlc_start, int size)
{
	t_mlc	*tmp;

	while (mlc_start)
	{
		tmp = mlc_start;
		mlc_start = mlc_start->next;
		ft_delone_mlc(tmp, free);
	}
	exit (size);
}

t_mlc	*ft_find_mlc_elem(t_mlc *mlc_list, void *addr)
{
	while (mlc_list)
	{
		if (mlc_list->addr == addr)
			return (mlc_list);
		mlc_list = mlc_list->next;
	}
	return (NULL);
}

void	ft_cleanly_delone_mlc(t_mlc **mlc_start, void *addr)
{
	t_mlc	*target;
	t_mlc	*mlc_list;
	t_mlc	*mlc_prev;

	mlc_list = *mlc_start;
	mlc_prev = *mlc_start;
	target = ft_find_mlc_elem(*mlc_start, addr);
	while (mlc_list && target)
	{
		if (mlc_list == target)
		{
			if (mlc_list == *mlc_start)
				*mlc_start = mlc_list->next;
			else if (mlc_list->next)
				mlc_prev->next = mlc_list->next;
			else if (mlc_list->next == NULL)
				mlc_prev->next = NULL;
			return (ft_delone_mlc(mlc_list, free));
		}
		else
			mlc_prev = mlc_list;
		mlc_list = mlc_list->next;
	}
	free(addr);
	addr = NULL;
}

t_mlc	*ft_malloc_list_add_back(t_mlc **mlc_list, t_mlc *new_mlc)
{
	t_mlc	*head;

	head = *mlc_list;
	if (!*mlc_list)
	{
		*mlc_list = new_mlc;
		(*mlc_list)->next = NULL;
		return (new_mlc);
	}
	else
	{
		while ((*mlc_list)->next)
			*mlc_list = (*mlc_list)->next;
		(*mlc_list)->next = new_mlc;
		new_mlc->next = NULL;
		return (head);
	}
}
