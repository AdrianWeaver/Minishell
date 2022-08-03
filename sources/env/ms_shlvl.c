/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:37:29 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/03 10:37:29 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_increment_shlvl(t_env *shlvl)
{
	int		shlvl_int;
	int		i;

	i = 0;
	while (shlvl->content[i])
	{
		if (ft_isdigit(shlvl->content[i]) == 0)
		{
			ft_replace_env_content(shlvl, ft_strdup("1"));
			return ;
		}
		i++;
	}
	shlvl_int = ft_atoi(shlvl->content);
	shlvl_int++;
	ft_replace_env_content(shlvl, ft_itoa(shlvl_int));
}

void	ft_update_shlvl(t_env *env)
{
	t_env	*shlvl;

	shlvl = ft_find_env_elem(env, "SHLVL");
	if (shlvl == NULL)
		ft_manually_add_one_env(env, "SHLVL", "1");
	else
		ft_increment_shlvl(shlvl);
}
