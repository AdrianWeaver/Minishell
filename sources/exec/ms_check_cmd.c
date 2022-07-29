/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:05:52 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/28 18:21:13 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_cmd(char *cmd)
{
	int	i;

	i = -1;
	if (cmd)
		while (cmd[++i])
			if ((cmd[0] != '\0') &&(cmd[i] != '/' && cmd[i] != '.'))
				break ;
	if (i != 0 && cmd[i] == '\0')
	{
		ft_eprintf("minishell: %s: %s\n", cmd, IS_DIR);
		return (-1);
	}
	return (0);
}

static int	ft_is_a_builtin(t_arg *arg)
{
	while (arg && arg->token != TOKEN_CMD)
		arg = arg->next;
	if ((arg && ft_strcmp(arg->content, "echo") == 0)
		|| (arg && ft_strcmp(arg->content, "env") == 0)
		|| (arg && ft_strcmp(arg->content, "pwd") == 0)
		|| (arg && ft_strcmp(arg->content, "cd") == 0)
		|| (arg && ft_strcmp(arg->content, "export") == 0)
		|| (arg && ft_strcmp(arg->content, "unset") == 0)
		|| (arg && ft_strcmp(arg->content, "exit") == 0))
		return (1);
	return (0);
}

int	ft_check_pipes(t_arg *arg, t_env *env, int std[2])
{
	int		pipes;
	int		*currents;

	pipes = ft_count_pipes(arg);
	if (pipes == 0)
	{
		if (ft_is_a_builtin(arg) == 1)
		{
			currents = ft_redirection(arg);
			ft_builtin_parser(&env, arg, std);
			if (currents[0] != 0)
				close(currents[0]);
			if (currents[1] != 1)
				close(currents[1]);
		}
		else
			ft_try(arg, env, pipes, std);
	}
	else
		ft_try(arg, env, pipes, std);
	return (pipes);
}
