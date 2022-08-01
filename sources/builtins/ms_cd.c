/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:04:22 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/01 09:26:33 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_pwd(t_env *env, char *path, t_env *env_pwd, int std[2])
{
	if (env_pwd == NULL)
		ft_manually_add_one_env(env, "PWD", path);
	else
	{
		env_pwd->content = ft_magic_malloc(FREE, 0, env_pwd->content);
		env_pwd->content = ft_get_pwd(std);
	}
}

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
	char	*pwd;
	t_env	*env_pwd;
	t_env	*env_oldpwd;
	int		success;

	if (ft_check_cd_args(path) == 1)
		return (1);
	pwd = ft_get_pwd(std);
	success = chdir(*path);
	if (success == 0)
	{
		env_pwd = ft_find_env_elem(env, "PWD");
		ft_check_pwd(env, *path, env_pwd, std);
		env_oldpwd = ft_find_env_elem(env, "OLDPWD");
		if (env_oldpwd == NULL)
			ft_manually_add_one_env(env, "OLDPWD", pwd);
		else
		{
			env_oldpwd->content = ft_magic_malloc(FREE, 0,
					env_oldpwd->content);
			env_oldpwd->content = pwd;
		}
		return (0);
	}
	return (ft_eprintf("cd: %s\n", strerror(errno)), 1);
}
