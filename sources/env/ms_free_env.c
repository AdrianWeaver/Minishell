/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:27:33 by aweaver           #+#    #+#             */
/*   Updated: 2022/06/23 14:01:58 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************ */
/*	ACT : frees a char **str											    */
/*	ARG : a char **str														*/
/*	RET : void																*/
/* ************************************************************************ */
void	ft_free_double_array(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_magic_malloc(FREE, 0, str[i]);
		i++;
	}
	str = ft_magic_malloc(FREE, 0, str);
}

/* ************************************************************************ */
/*	ACT : deletes an element (t_env) of a t_env list saving the list pointer*/
/*	ARG : the address of the first element of the list and the address of 	*/
/*	the element meant to be removed											*/
/*	RET : void																*/
/* ************************************************************************ */

//one case needs to be addressed if env is composed of only 1 element.
void	ft_cleanly_delone_env(t_env **env_start, t_env *target)
{
	t_env	*env_list;
	t_env	*env_prev;

	env_list = *env_start;
	env_prev = *env_start;
	while (env_list && target)
	{
		if (env_list == target)
		{
			if (env_list == *env_start)
				*env_start = env_list->next;
			else if (env_list->next)
				env_prev->next = env_list->next;
			else if (env_list->next == NULL)
				env_prev->next = NULL;
			ft_delone_env(env_list, free);
			return ;
		}
		else
			env_prev = env_list;
		env_list = env_list->next;
	}
}

/* ************************************************************************ */
/*	ACT : deletes an element (t_env) of a t_env list breaking the list		*/
/*	ARG : a t_env and a function returning void and taking a void pointer	*/
/*	RET : void																*/
/* ************************************************************************ */

void	ft_delone_env(t_env *env, void (*del)(void *))
{
	if (!env)
		return ;
	del(env->name);
	env->name = NULL;
	del(env->content);
	env->content = NULL;
	del(env);
}

/* ************************************************************************ */
/*	ACT : deletes cleanly the env											*/
/*	ARG : the first element of the env										*/
/*	RET : void																*/
/* ************************************************************************ */
void	ft_free_env(t_env *env_start)
{
	t_env	*tmp;

	while (env_start)
	{
		tmp = env_start;
		env_start = env_start->next;
		ft_delone_env(tmp, free);
	}
}
