/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:27:33 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/09 19:20:41 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_double_array(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_env_delone(t_env *env, void (*del)(void *))
{
	//int	i;
//
	//i = 0;
	del(env->name);
	if (env->content)
		ft_free_double_array(env->content);
	//while ((env->content[i]))
	//{
		//del(env->content[i]);
		//i++;
	//}
	//del(env->content);
	del(env);
}

void	ft_free_env(t_env **env_start)
{
	t_env	**save_env_start;
	t_env	*tmp;

	save_env_start = env_start;
	while (*env_start)
	{
		tmp = *env_start;
		*env_start = (*env_start)->next;
		ft_env_delone(tmp, free);
	}
	free(save_env_start);
}
