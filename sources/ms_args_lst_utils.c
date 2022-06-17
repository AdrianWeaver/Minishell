/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_args_lst_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:13:30 by jcervoni          #+#    #+#             */
/*   Updated: 2022/04/12 14:28:48 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* creation et manipulation de la liste des arguments */

t_arg	*ft_newarg(char *argv)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->token = NULL;
	new->content = argv;
	new->next = NULL;
	return (new);
}

t_arg	*ft_lastarg(t_arg *arg)
{
	t_arg	*temp;
	
	temp = arg;
	if (!arg)
		return (NULL);
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	ft_addarg_back(t_arg **argl, t_arg *new)
{
	t_arg	*temp;

	if(argl)
	{
		if (*argl == NULL)
			*argl = new;
		else
		{
			temp = ft_lastarg(*(argl));
			temp->next = new;
		}
	}
}

int	ft_argsize(t_arg *arg)
{
	int		i;
	t_arg	*temp;
	
	i = 0;
	temp = arg;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	ft_cleararg(t_arg *arg)
{
	t_arg	*temp;
	t_arg	*clear;
	
	temp = arg;
	while (temp->next != NULL)
	{
		clear = temp;
		temp = temp->next;
		free(clear);
	}
	free(temp);
}