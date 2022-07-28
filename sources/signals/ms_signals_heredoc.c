/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 10:53:13 by aweaver           #+#    #+#             */
/*   Updated: 2022/07/28 20:10:24 by aweaver          ###   ########.fr       */
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
}

static void	ft_ignore_heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		(void)signum;
		write(2, "\n", 1);
	}
}

void	ft_ignore_signal_heredoc(void)
{
	struct sigaction	action_heredoc;

	sigemptyset(&action_heredoc.sa_mask);
	action_heredoc.sa_flags = SA_NODEFER;
	action_heredoc.sa_handler = &ft_ignore_heredoc_handler;
	sigaction(SIGINT, &action_heredoc, 0);
}

void	ft_signal_catching_heredoc(void)
{
	struct sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_NODEFER;
	action.sa_handler = &ft_my_magic_handler_heredoc;
	sigaction(SIGINT, &action, 0);
}

void	ft_ignore_handler(int signum)
{
	(void)signum;
	write(2, "\n", 1);
}
