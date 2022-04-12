/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_mlc_lst_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:34:33 by jcervoni          #+#    #+#             */
/*   Updated: 2022/04/12 14:51:12 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mlc	*ft_newmlc(void *adr)
{
	t_mlc	*new;

	new = malloc(sizeof(t_mlc));
	if (!new)
		return (NULL);
	new->ptr = adr;
	new->next = NULL;
	return (new);
}

t_mlc	*ft_lastmlc(t_mlc *mlc)
{
	t_mlc	*temp;
	
	temp = mlc;
	if (!mlc)
		return (NULL);
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	ft_addmlc_back(t_mlc **mlcl, t_mlc *new)
{
	t_mlc	*temp;

	if(mlcl)
	{
		if (*mlcl == NULL)
			*mlcl = new;
		else
		{
			temp = ft_lastmlc(*(mlcl));
			temp->next = new;
		}
	}
}

int	ft_mlcsize(t_mlc *mlc)
{
	int		i;
	t_mlc	*temp;

	i = 0;
	temp = mlc;
	while (temp !=NULL)
	{
		temp=temp->next;
		i++;
	}
	return (i);
}

void	ft_clearmlc(t_mlc *mlc)
{
	t_mlc	*temp;
	t_mlc	*clear;
	
	temp = mlc;
	if (mlc)
	{	
		while (temp->next != NULL)
		{
			clear = temp;
			free(clear->ptr);
			free(clear);
			temp = temp->next;		
		}
		free(temp->ptr);
		free(temp);
	}
}