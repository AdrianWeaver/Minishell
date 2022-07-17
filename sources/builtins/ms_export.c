/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@42.fr>                     +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:29:15 by aweaver           #+#    #+#             */
/*   Updated: 2022/07/14 14:55:24 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************ */
/*	ACT: finds the element of the list with env->name == param				*/
/*	ARG: the env as a list, a char *name									*/
/*	RET: returns the address of the element seeked for						*/
/* ************************************************************************ */

void	ft_export_check_haters(t_env **env_list, t_env *to_add)
{
	int		i;
	t_env	*old_env_var;

	i = 0;
	old_env_var = ft_find_env_elem(*env_list, to_add->name);
	while (to_add->name[i])
	{
		if (to_add->name[i] == '+' && to_add->name[i + 1] == '\0')
		{
			old_env_var->content = ft_strjoin_free(old_env_var->content,
					to_add->content);
			ft_magic_malloc(FREE, 0, to_add);
			break ;
		}
		else if (to_add->name[i] != '\0' && to_add->name[i + 1] == '\0')
		{
			ft_env_add_back(env_list, to_add);
			ft_cleanly_delone_env(env_list, old_env_var);
			break ;
		}
		i++;
	}
}

/****************************************************************************
 * ACT: Checks if the var that is to be added doesnt already exist in env
 * ARG: the env as a list, the new element as an element of a list
 * RET: void
 * *************************************************************************/

void	ft_deal_with_existing_env_var(t_env **env_list, t_env *to_add)
{
	t_env	*old_env_var;

	old_env_var = ft_find_env_elem(*env_list, to_add->name);
	if (old_env_var != NULL)
	{
		ft_export_check_haters(env_list, to_add);
	}
	else
	{
		ft_env_add_back(env_list, to_add);
	}
}

/****************************************************************************
 * ACT: replicates the export function
 * ARG: the env as a list, a char **to_add (result of the parsing)
 * RET: man says exit status is always 0.
 * 		here returns 0 or >0 if one of the args failed
 * *************************************************************************/

int	ft_export(t_env **env_list, char **to_add)
{
	t_env	*tmp_element;
	int		ret;

	ret = 0;
	if (ft_array_size(to_add) == 0)
		return (ft_eprintf("export: not enough arguments\n"), 1);
	while (*to_add)
	{
		tmp_element = ft_get_env_element(*env_list, *to_add);
		if (ft_is_valid_env_variable(tmp_element->name) == 1)
		{
			ft_deal_with_existing_env_var(env_list, tmp_element);
		}
		else
		{
			ft_eprintf("export: `%s': not a valid identifier\n", *to_add);
			ft_delone_env(tmp_element);
			ret++;
		}
		to_add++;
	}
	return (ret);
}
