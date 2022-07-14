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

int	ft_try(t_arg *arg, t_env *env)
{
	char	**env_tab;
	char	**paths;
	char	**args_tab;

	fprintf(stderr, "1\n");
	env_tab = ft_env_to_char(env);
	fprintf(stderr, "2\n");
	paths = ft_get_path(env);
	fprintf(stderr, "3\n");
	args_tab = ft_list_to_char(arg);
	fprintf(stderr, "4\n");
	ft_exec(args_tab, paths, env_tab);
	return (0);
}
