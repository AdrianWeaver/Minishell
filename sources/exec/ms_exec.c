/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 08:30:54 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/13 08:31:44 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_pipes(t_arg *arg)
{
	int	i;

	i = 0;
	while (arg)
	{
		if (arg->token == TOKEN_PIPE)
			i++;
		arg = arg->next;
	}
	return (i);
}

int	ft_try(t_arg *arg, t_env *env)
{
	char	**env_tab;
	char	**paths;
	char	**args_tab;
	// int		pipes;
	// int		i;

	// i = 0;
	env_tab = ft_env_to_char(env);
	paths = ft_get_path(env);
	// pipes = ft_count_pipes(arg);
	while (arg)
	{
		args_tab = ft_list_to_char(arg);
		ft_exec(args_tab, paths, env_tab);
	}
	return (0);
}


// int	ft_exec(char **cmds, t_env *env)
// {
// 	char	**paths;
// 	char	**env_tab;
// }