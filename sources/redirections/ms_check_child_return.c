/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_child_return.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:15:45 by aweaver           #+#    #+#             */
/*   Updated: 2022/07/28 20:16:38 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_signal_return_code(int signal_code)
{
	if (signal_code == SIGINT)
		return (130);
	if (signal_code == SIGQUIT)
		return (131);
	if (signal_code == SIGKILL || signal_code == SIGTERM)
		return (143);
	if (signal_code == SIGSTOP)
		return (148);
	if (signal_code == SIGABRT)
		return (143);
	else
		return (0);
}

int	ft_check_child_return(pid_t child_pid)
{
	int		child_status;
	int		child_return;

	child_return = 0;
	waitpid(child_pid, &child_status, 0);
	if (WIFEXITED(child_status))
	{
		child_return = WEXITSTATUS(child_status);
		g_ret_value = child_return;
		if (child_return == 130)
		{
			g_ret_value = 130;
			return (130);
		}
	}
	else if (WIFSIGNALED(child_status))
	{
		child_return = WTERMSIG(child_status);
		g_ret_value = ft_get_signal_return_code(child_return);
		return (child_return);
	}
	return (0);
}
