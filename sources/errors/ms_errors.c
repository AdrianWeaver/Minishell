/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:15:00 by jcervoni          #+#    #+#             */
/*   Updated: 2022/04/14 16:43:58 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*	ACT : free all malloc'd pointers and exit with exit code 1                */
/*	ARG : a pointer to the first element of a t_mlc list                      */
/*	RET : exit code 1                                                         */
/* ************************************************************************** */

void	ft_exit(t_mlc *mlc)
{
	ft_clearmlc(mlc);
	exit(1);
}

/* ************************************************************************** */
/*	ACT : calloc ptrs and store address in a newly created t_mlc element      */
/*	ARG : size to allocate                                                    */
/*	RET : a poiter to the allocated address                                   */
/* ************************************************************************** */

void	*ft_custom_calloc(int size)
{
	static t_mlc	*lmlc;
	t_mlc			*new;
	void			*adr;

	lmlc = NULL;
	if (size < 0)
		ft_exit(lmlc);
	adr = ft_calloc(1, size);
	if (!adr)
		ft_exit(lmlc);
	new = ft_newmlc(adr);
	if (!new)
	{
		free(adr);
		ft_exit(lmlc);
	}
	ft_addmlc_back(&lmlc, new);
	return (adr);
}
