/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:35:51 by jcervoni          #+#    #+#             */
/*   Updated: 2022/06/23 16:48:02 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_prompt(t_env *env_list)
{
	t_env	*tmp;
	char	*name;
	char	*cwd;
	char	*path;

	tmp = NULL;
	name = NULL;
	cwd = ft_get_pwd();
	tmp = ft_find_env_elem(env_list, "USER");
	path = ft_get_short_path(tmp, cwd);
	if (!tmp || !cwd)
		return (NULL);
	name = ft_strdup(tmp->content);
	name = ft_strjoin_free(name, ":");
	name = ft_strjoin_free(name, path);
	name = ft_strjoin_free(name, "$ ");
	path = ft_magic_malloc(FREE, 0, path);
	cwd = ft_magic_malloc(FREE, 0, cwd);
	return (name);
}

char	*ft_get_short_path(t_env *user, char *cwd)
{
	char	*path;
	char	*tmp;
	int		i;

	path = NULL;
	tmp = NULL;
	i = 0;
	while (cwd[i])
	{
		path = ft_strchr(&cwd[i], user->content[0]);
		if (path)
		{
			if (ft_strncmp(path, user->content, ft_strlen(user->content)) == 0)
			{
				tmp = ft_strdup(&path[ft_strlen(user->content) + 1]);
				ft_magic_malloc(ADD, 0, tmp);
				path = ft_strjoin("~/", tmp);
				tmp = ft_magic_malloc(FREE, 0, NULL);
				return (path);
			}
		}
		i++;
	}
	return (cwd);
}
