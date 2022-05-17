/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:30:29 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/17 14:30:44 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************ */
/*	ACT: checks if str is a valid env variable								*/
/*	ARG: a char *str														*/
/*	RET: 1 if true 0 if false												*/
/* ************************************************************************ */

int	ft_is_valid_env_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
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
