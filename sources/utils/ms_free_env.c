/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:27:33 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/10 17:37:40 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* DEPRECATED */
void	ft_free_double_array(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	printf("str addr = %p\n", str);
}

void	ft_env_delone(t_env *env, void (*del)(void *))
{
	int	i;

	i = 0;
	del(env->name);
	if (env->content)
	{
		while ((env->content[i]))
		{
			del(env->content[i]);
			i++;
		}
		del(env->content);
	}
	del(env);
}

void	ft_free_env(t_env *env_start)
{
	t_env	*tmp;

	while (env_start)
	{
		tmp = env_start;
		env_start = env_start->next;
		printf("NAME=%s\n", tmp->name);
		ft_env_delone(tmp, free);
	}
}
