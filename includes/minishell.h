/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:18:31 by aweaver           #+#    #+#             */
/*   Updated: 2022/04/12 17:57:59 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "minishell_struct.h"

/* ************************************************************************** */
/*                                  PARSING                                   */
/* ************************************************************************** */

/* ************************************ */
/*              ARGS TOOLS              */
/* ************************************ */

t_arg	*ft_newarg(char *argv);
t_arg	*ft_lastarg(t_arg *arg);
void	ft_addarg_back(t_arg **argl, t_arg *new);
void	ft_cleararg(t_arg *arg);
int		ft_argsize(t_arg *arg);

/* ************************************ */
/*              ARGS TOOLS              */
/* ************************************ */

t_mlc	*ft_newmlc(void *adr);
t_mlc	*ft_lastmlc(t_mlc *mlc);
void	ft_addmlc_back(t_mlc **mlcl, t_mlc *new);
void	ft_clearmlc(t_mlc *mlc);
int		ft_mlcsize(t_mlc *mlc);

#endif
