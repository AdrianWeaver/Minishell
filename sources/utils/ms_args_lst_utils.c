/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_args_lst_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:13:30 by jcervoni          #+#    #+#             */
/*   Updated: 2022/06/23 16:46:17 by aweaver          ###   ########.fr       */
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

	new = ft_magic_malloc(MALLOC, sizeof(t_arg), NULL);
	if (!new)
		return (NULL);
	new->content = ft_strdup(argv);
	ft_magic_malloc(ADD, 0, new->content);
	if (!new->content)
		return (NULL);
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
	if (!arg)
		return (NULL);
	while (arg->next != NULL)
		arg = arg->next;
	return (arg);
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

	i = 0;
	while (arg != NULL)
	{
		arg = arg->next;
		i++;
	}
	return (i);
}

/* ************************************************************************** */
/*	ACT : free all elements of a t_arg list                                   */
/*	ARG : a pointer to a t_arg element                                        */
/*	RET : none                                                                */
/* ************************************************************************** */

void	ft_clear_arg(t_arg *arg)
{
	t_arg	*clear;

	if (arg)
	{
		while (arg->next != NULL)
		{
			clear = arg;
			arg = arg->next;
			clear->content = ft_magic_malloc(FREE, 0, clear->content);
			clear = ft_magic_malloc(FREE, 0, clear);
		}
	arg->content = ft_magic_malloc(FREE, 0, arg->content);
	arg = ft_magic_malloc(FREE, 0, arg);
	}
}
