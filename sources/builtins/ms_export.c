/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:29:15 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/17 16:54:59 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_env *env_list, char **to_add)
{
	t_env	*tmp_element;
	t_env	*old_env_var;
	int		ret;

	ret = 0;
	while (*to_add)
	{
		old_env_var = ft_find_env_elem(t_env *env_list, char
		tmp_element = ft_get_env_element(*to_add);
		if (ft_is_valid_env_variable(tmp_element->name) == 1)
			ft_env_add_back(&env_list, tmp_element);
		else
		{
			fprintf(stderr, "export: '%s': not valid identifier", tmp_element->name);
			ft_delone_env(tmp_element, free);
			ret++;
		}
		to_add++;
	}
	return (ret);
}
