/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:04:22 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/25 10:06:48 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_env *env, char *path)
{
	char	*pwd;
	t_env	env_pwd;
	int		success;

	pwd = ft_get_pwd();
	success = chdir(path);
	if (success == 0)
	{
		env_pwd = ft_find_env_elem(env, "PWD");
		if (env_pwd == NULL)
			ft_manually_add_one_env(env, "PWD", path);
		else
		{
			free(old_pwd->content);
			env_pwd->content = ft_get_pwd();
		}
	}
}
