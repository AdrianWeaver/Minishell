/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:15:00 by jcervoni          #+#    #+#             */
/*   Updated: 2022/04/14 10:45:44 by jcervoni         ###   ########.fr       */
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
