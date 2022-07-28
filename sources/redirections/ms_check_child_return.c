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

int	ft_check_child_return(pid_t child_pid)
{
	int		child_status;

	waitpid(child_pid, &child_status, 0);
	if (WIFEXITED(child_status))
	{
		if (WEXITSTATUS(child_status) == 130)
		{
			g_ret_value = 130;
			return (130);
		}
	}
	else if (WIFSIGNALED(child_status))
	{
		return (WTERMSIG(child_status));
	}
	return (0);
}
