/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_child_return.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:15:45 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/02 14:55:42 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_signal_return_code(int signal_code)
{
	return (128 + signal_code);
}

int	ft_check_child_return(pid_t child_pid)
{
	int		child_status;
	int		child_return;

	child_return = 0;
	child_status = 0;
	waitpid(child_pid, &child_status, 0);
	if (WIFEXITED(child_status))
	{
		child_return = WEXITSTATUS(child_status);
		g_ret_value = child_return;
		if (child_return == 130)
			return (130);
		return (child_return);
	}
	else if (WIFSIGNALED(child_status))
	{
		child_return = WTERMSIG(child_status);
		child_return = ft_get_signal_return_code(child_return);
		return (child_return);
	}
	return (0);
}
