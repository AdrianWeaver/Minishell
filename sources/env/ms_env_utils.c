/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:25:39 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/02 10:12:16 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************ */
/*	ACT: finds the size of an env list										*/
/*	ARG: an env as a list													*/
/*	RET: the size of the env_ist as an int									*/
/* ************************************************************************ */

int	ft_env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}

/* ************************************************************************ */
/*	ACT: checks if str is a valid env variable								*/
/*	ARG: a char *str														*/
/*	RET: 1 if true 0 if false												*/
/* ************************************************************************ */

int	ft_is_valid_env_variable(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] == 0)
		return (0);
	if (ft_isdigit(str[0]) == 1)
		return (0);
	ft_eprintf("str dans export == %s\n", str);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (i);
}

/* ************************************************************************ */
/*	ACT: finds the element of the list with env->name == param				*/
/*	ARG: the env as a list, a char *name									*/
/*	RET: returns the address of the element seeked for						*/
/* ************************************************************************ */

t_env	*ft_find_env_elem(t_env *env_list, char *name)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->name, name) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

/* ************************************************************************ */
/*	ACT: finds the element of the list with env->name == param				*/
/*	ARG: the env as a list, a char *name									*/
/*	RET: returns the address of the element seeked for						*/
/* ************************************************************************ */

void	ft_manually_add_one_env(t_env *env_list, char *name, char *content)
{
	t_env	*env_set;
	t_env	*env_new;

	if (ft_is_valid_env_variable(name) != 0)
	{
		env_set = ft_find_env_elem(env_list, name);
		if (env_set)
		{
			env_set->content = ft_magic_malloc(FREE, 0, env_set->content);
			if (content == NULL)
				env_set->content = NULL;
			else
				env_set->content = ft_magic_malloc(ADD, 0, ft_strdup(content));
		}
		else
		{
			env_new = ft_magic_malloc(MALLOC, sizeof(*env_new) * 1, NULL);
			env_new->name = ft_magic_malloc(ADD, 0, ft_strdup(name));
			if (content == NULL)
				env_set->content = NULL;
			else
				env_new->content = ft_magic_malloc(ADD, 0, ft_strdup(content));
			ft_env_add_back(&env_list, env_new);
		}
	}
}
