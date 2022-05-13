/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:58:52 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/13 16:09:10 by aweaver          ###   ########.fr       */
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
		if (ft_is_alnum(str[i] == 1) && str[i] != '_')
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
}

/* ************************************************************************ */
/*	ACT: replicate unset function behaviour									*/
/*	ARG: the env as a list, several char * as param names					*/
/*	RET: void but prints error if incorrect format for names given			*/
/* ************************************************************************ */

void	*ft_unset(t_env *env_list, char *name, ...)
{
	t_env	*target;
	char	*target_name;
	va_list	to_erase;

	va_start(to_erase, name);
	while (to_erase)
	{
		target_name = (char *) va_arg(to_erase);
		if (ft_is_valid_env_variable(target_name) == 1)
		{
			target = ft_find_env_elem(env_list, target_name);
			if (target != 0)
				ft_cleanly_delone_env(&env_list, target);
		}
		else
			fprintf(stderr, "unset: %s: invalid parameter name", name);
		to_erase++;
	}
	va_end(to_erase);
}
