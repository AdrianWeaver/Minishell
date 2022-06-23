/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:04:22 by aweaver           #+#    #+#             */
/*   Updated: 2022/06/23 13:51:54 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (env_pwd == NULL)
			ft_manually_add_one_env(env, "PWD", path);
		else
		{
			env_pwd->content = ft_magic_malloc(FREE, 0, env_pwd->content);
			env_pwd->content = ft_get_pwd();
		}
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
	fprintf(stderr, "cd: no such file or directory: %s", path);
	return (1);
}
