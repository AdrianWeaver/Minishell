/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_args_lst_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:13:30 by jcervoni          #+#    #+#             */
/*   Updated: 2022/04/14 10:44:04 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*	ACT : create a new element t_arg with content of argv                     */
/*	ARG : char *argv from terminal input                                      */
/*	RET : a pointer to the created element                                    */
/* ************************************************************************** */

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

/* ************************************************************************** */
/*	ACT : find the last element of a t_arg list                               */
/*	ARG : a pointer to a t_arg element                                        */
/*	RET : a pointer to the last element                                       */
/* ************************************************************************** */

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

/* ************************************************************************** */
/*	ACT : add a new element t_arg at the queue of a t_arg list                */
/*	ARG : a pointer to a t_arg list, a pointer to a t_arg element             */
/*	RET : none                                                                */
/* ************************************************************************** */

void	ft_addarg_back(t_arg **argl, t_arg *new)
{
	t_arg	*temp;

	if (argl)
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

/* ************************************************************************** */
/*	ACT : calculate the size of a t_arg list                                  */
/*	ARG : a pointer to a t_arg element                                        */
/*	RET : an int (size)                                                       */
/* ************************************************************************** */

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

/* ************************************************************************** */
/*	ACT : free all elements of a t_arg list                                   */
/*	ARG : a pointer to a t_arg element                                        */
/*	RET : none                                                                */
/* ************************************************************************** */

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
