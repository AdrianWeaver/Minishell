/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:10:20 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/11 13:51:34 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef struct s_arg
{
	int				token;
	char			*content;
	struct s_arg	*next;
}	t_arg;

typedef struct s_mlc
{
	void			*ptr;
	struct s_mlc	*next;
}	t_mlc;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;	

#endif
