/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:04:22 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/02 13:42:29 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_cd_args(char **path)
{
	if (ft_array_size(path) > 1)
		return (ft_eprintf("cd: too may arguments\n"), 1);
	else if (ft_array_size(path) < 1)
		return (ft_eprintf("cd: not enough arguments\n"), 1);
	else
		return (0);
}

int	ft_cd(t_env *env, char **path, int std[2])
{
	t_env	*env_pwd;
	int		success;
	char	*new_path;

	(void)std[2];
	if (ft_check_cd_args(path) == 1)
		return (1);
	env_pwd = ft_find_env_elem(env, "PWD");
	if (env_pwd == NULL)
		ft_manually_add_one_env(env, "PWD", NULL);
	env_pwd = ft_find_env_elem(env, "PWD");
	success = chdir(*path);
	if (success == 0)
	{
		ft_manually_add_one_env(env, "OLDPWD", env_pwd->content);
		new_path = ft_get_pwd(std);
		ft_manually_add_one_env(env, "PWD", new_path);
		new_path = ft_magic_malloc(FREE, 0, new_path);
		return (0);
	}
	return (ft_eprintf("cd: %s\n", strerror(errno)), 1);
}
