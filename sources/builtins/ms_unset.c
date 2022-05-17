/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:58:52 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/17 10:09:42 by aweaver          ###   ########.fr       */
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
		if (ft_isalnum(str[i] == 1) && str[i] != '_')
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

/* ************************************************************************ */
/*	ACT: replicate unset function behaviour									*/
/*	ARG: the env as a list, several char * as param names					*/
/*	RET: void but prints error if incorrect format for names given			*/
/* ************************************************************************ */

int	ft_unset(t_env *env_list, char **to_erase)
{
	t_env	*target;
	int		ret;

	ret = 0;
	while (*to_erase)
	{
		if (ft_is_valid_env_variable(*to_erase) == 1)
		{
			target = ft_find_env_elem(env_list, *to_erase);
			if (target != 0)
				ft_cleanly_delone_env(&env_list, target);
			if (target == NULL)
				ret++;
		}
		else
			fprintf(stderr, "unset: %s: invalid parameter name", *to_erase);
		to_erase++;
	}
	return (ret);
}
