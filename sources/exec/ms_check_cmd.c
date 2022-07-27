/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:05:52 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/27 07:49:26 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_cmd(char *cmd)
{
	int	i;

	i = -1;
	if (cmd)
		while (cmd[++i])
			if (cmd[i] != '/' && cmd[i] != '.')
				break ;
	if (cmd[i] == '\0')
	{
		ft_eprintf("minishell: %s: %s\n", cmd, IS_DIR);
		return (-1);
	}
	return (0);
}

int	ft_check_pipes(t_arg *arg, t_env *env, int std[2])
{
	int		pipes;
	int		*currents;

	pipes = ft_count_pipes(arg);
	if (pipes == 0)
	{
		ft_redir_heredoc(arg, env, std);
		currents = ft_redirection(arg);
		if (ft_builtin_parser(&env, arg, std) == 42)
			ft_try(arg, env, pipes, std);
		else
		{
			if (currents[0] != 0)
				close(currents[0]);
			if (currents[1] != 1)
				close(currents[1]);
		}	
	}
	else
		ft_try(arg, env, pipes, std);
	return (pipes);
}
