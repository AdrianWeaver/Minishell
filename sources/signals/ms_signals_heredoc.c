/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 10:53:13 by aweaver           #+#    #+#             */
/*   Updated: 2022/07/27 12:10:14 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	ft_my_magic_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		get_next_line(GNL_FLUSH);
		ft_magic_malloc(FLUSH, 130, NULL);
		exit(130);
	}
	if (signum == SIGQUIT)
	{
		(void)signum;
	}
}

void	ft_signal_catching_heredoc(void)
{
	struct sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	action.sa_handler = &ft_my_magic_handler_heredoc;
	sigaction(SIGINT, &action, 0);
}

void	ft_ignore_handler(int signum)
{
	(void)signum;
}
