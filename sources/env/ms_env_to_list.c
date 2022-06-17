/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:31:25 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/12 14:46:00 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*	ACT : returns the last element of a list						          */
/*	ARG : a t_env *list											              */
/*	RET : a pointer on the last element of the list given as input			  */
/* ************************************************************************** */

t_env	*ft_env_last(t_env *env)
{
	while (env)
	{
		if (env->next == NULL)
			return (env);
		env = env->next;
	}
	return (env);
}

/* ************************************************************************** */
/*	ACT : adds the new element at the end of the env_list given as input	  */
/*	ARG : a t_env **env_start beginning of the list, a t_env *new to be added */
/*	RET : void																  */
/* ************************************************************************** */

void	ft_env_add_back(t_env **env_start, t_env *new)
{
	t_env	*last;

	if (*env_start == NULL)
	{
		*env_start = new;
		return ;
	}
	else
	{
		last = ft_env_last(*env_start);
		last->next = new;
	}
}

/* ************************************************************************** */
/*	ACT : Used by ft_env_to_list to retrieve one line of the env	          */
/*	ARG : one line of the env given as a char *		                          */
/*	RET : a pointer on the created struct with name and content filled        */
/* ************************************************************************** */

t_env	*ft_get_env_element(char *env_line)
{
	int			i;
	char		*tmp_str;
	t_env		*tmp_element;

	i = 0;
	tmp_element = malloc(sizeof(*tmp_element) * 1);
	while (env_line[i] && env_line[i] != '=')
		i++;
	tmp_str = ft_strndup(env_line, i);
	tmp_element->name = tmp_str;
	if (env_line[i] == '=')
	{
		tmp_element->content = ft_split(&env_line[i] + 1, ':');
		i++;
	}
	tmp_element->next = NULL;
	return (tmp_element);
}

/* ************************************************************************** */
/*	ACT : creates the env that will be used by the minishell                  */
/*	ARG : the env given as a char **				                          */
/*	RET : a pointer on the first element of the created struct                */
/* ************************************************************************** */

t_env	*ft_env_to_list(char **env)
{
	t_env	*env_start;
	t_env	*tmp_element;

	env_start = NULL;
	while (*env)
	{
		tmp_element = ft_get_env_element(*env);
		ft_env_add_back(&env_start, tmp_element);
		env++;
	}
	return (env_start);
}
