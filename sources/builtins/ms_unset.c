/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@42.fr>                     +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:58:52 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/17 14:31:23 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************ */
/*	ACT: replicate unset function behaviour									*/
/*	ARG: the env as a list, several char * as param names					*/
/*	RET: void but prints error if incorrect format for names given			*/
/* ************************************************************************ */

int	ft_unset(t_env **env_list, char **to_erase)
{
	t_env	*target;
	int		ret;

	ret = 0;
	while (*to_erase)
	{
		if (ft_is_valid_env_variable(*to_erase) == 1)
		{
			target = ft_find_env_elem(*env_list, *to_erase);
			if (target == NULL)
				ret++;
			else
				ft_cleanly_delone_env(env_list, target);
		}
		else
		{
			ret++;
			ft_eprintf("unset: '%s': not a valid identifier\n", *to_erase);
		}
		to_erase++;
	}
	return (ret);
}
