/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:04:22 by aweaver           #+#    #+#             */
/*   Updated: 2022/06/27 19:11:06 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_pwd(t_env *env, char *path, t_env *env_pwd)
{
	if (env_pwd == NULL)
		ft_manually_add_one_env(env, "PWD", path);
	else
	{
		env_pwd->content = ft_magic_malloc(FREE, 0, env_pwd->content);
		env_pwd->content = ft_get_pwd();
	}
}

int	ft_cd(t_env *env, char *path)
{
	char	*pwd;
	t_env	*env_pwd;
	t_env	*env_oldpwd;
	int		success;

	pwd = ft_get_pwd();
	success = chdir(path);
	if (success == 0)
	{
		env_pwd = ft_find_env_elem(env, "PWD");
		ft_check_pwd(env, path, env_pwd);
		env_oldpwd = ft_find_env_elem(env, "OLDPWD");
		if (env_oldpwd == NULL)
			ft_manually_add_one_env(env, "OLDPWD", pwd);
		else
		{
			env_oldpwd = ft_magic_malloc(FREE, 0, env_oldpwd->content);
			env_pwd->content = pwd;
		}
		return (0);
	}
	ft_eprintf("cd: no such file or directory: %s", path);
	return (1);
}
