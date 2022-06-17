/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:10:20 by jcervoni          #+#    #+#             */
/*   Updated: 2022/04/12 14:42:57 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef struct s_arg
{
	char			*token;
	char			*content;
	struct s_arg	*next;
}	t_arg;

typedef struct	s_mlc
{
	void			*ptr;
	struct s_mlc	*next;
}	t_mlc;

#endif