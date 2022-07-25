/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_to_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitch <mitch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:02:09 by aweaver           #+#    #+#             */
/*   Updated: 2022/07/17 12:37:54 by mitch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env_to_char(t_env *env)
{
	char	**tab;
	int		env_size;
	int		i;

	i = 0;
	env_size = ft_env_size(env);
	tab = ft_magic_malloc(MALLOC, sizeof(*tab) * (env_size + 1), NULL);
	tab[env_size] = 0;
	while (env)
	{
		tab[i] = ft_strjoin(env->name, "=");
		tab[i] = ft_strjoin_free(tab[i], env->content);
		ft_magic_malloc(ADD, 0, tab[i]);
		i++;
		env = env->next;
	}
	return (tab);
}
