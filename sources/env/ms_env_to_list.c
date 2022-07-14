/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:31:25 by aweaver           #+#    #+#             */
/*   Updated: 2022/07/14 17:58:54 by aweaver          ###   ########.fr       */
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
/*	ACT : Used to get the content of an env var and deals with +=             */
/*	ARG : the env as a list, name of var, content of var and flag + (0 or 1)  */
/*	RET : returns the created content                                         */
/* ************************************************************************** */

char	*ft_env_get_content(t_env *env_list, char *name, char *env_line,
		int flag_plus)
{
	t_env	*old_env;
	char	*joined;

	if (!env_line)
		return (NULL);
		//return (ft_magic_malloc(ADD, 0, ft_strdup("")));
	if (flag_plus == 0)
		return (ft_magic_malloc(ADD, 0, ft_strdup(env_line)));
	else
	{
		old_env = ft_find_env_elem(env_list, name);
		if (old_env == NULL)
			return (ft_magic_malloc(ADD, 0, ft_strdup(env_line)));
		else
		{
			joined = ft_magic_malloc(ADD, 0, ft_strjoin(old_env->content,
						env_line));
			old_env->content = ft_magic_malloc(FREE, 0, old_env->content);
			return (joined);
		}
	}
}

/* ************************************************************************** */
/*	ACT : Used by ft_env_to_list to retrieve one line of the env	          */
/*	ARG : one line of the env given as a char *		                          */
/*	RET : a pointer on the created struct with name and content filled        */
/* ************************************************************************** */

t_env	*ft_get_env_element(t_env *env_list, char *env_line)
{
	int			i;
	int			flag_plus;
	t_env		*tmp_element;

	i = 0;
	flag_plus = 0;
	tmp_element = ft_magic_malloc(MALLOC, sizeof(*tmp_element) * 1, NULL);
	while (env_line[i] && env_line[i] != '=')
	{
		if (env_line[i] == '+' && env_line[i + 1] == '=')
			flag_plus = 1;
		i++;
	}
	tmp_element->name = ft_strndup(env_line, i - flag_plus);
	ft_magic_malloc(ADD, 0, tmp_element->name);
	if (env_line[i] == '=')
	{
		i++;
		tmp_element->content = ft_env_get_content(env_list, tmp_element->name,
				&env_line[i], flag_plus);
	}
	else
		tmp_element->content = NULL;
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
		tmp_element = ft_get_env_element(env_start, *env);
		ft_env_add_back(&env_start, tmp_element);
		env++;
	}
	return (env_start);
}
