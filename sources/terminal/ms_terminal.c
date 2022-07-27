/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_terminal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:28:52 by aweaver           #+#    #+#             */
/*   Updated: 2022/07/27 13:40:18 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "minishell.h"

void	ft_set_term_behaviour(void)
{
	struct termios		term;

	if (ft_is_interactive())
	{
		if (tcgetattr(0, &term) == -1)
		{
			ft_eprintf("tcgetattr: %s\n", strerror(errno));
			ft_magic_malloc(FLUSH, 1, NULL);
		}
		term.c_lflag &= ~ECHOCTL;
		if (tcsetattr(0, 0, &term) == -1)
		{
			ft_eprintf("tcsetattr: %s\n", strerror(errno));
			ft_magic_malloc(FLUSH, 1, NULL);
		}
	}
}

int	ft_is_interactive(void)
{
	int	interactive_or_not;
	int	stdin_status;
	int	stdout_status;

	interactive_or_not = 0;
	stdin_status = isatty(STDIN_FILENO);
	stdout_status = isatty(STDERR_FILENO);
	if (stdin_status == 1 && stdout_status == 1)
		interactive_or_not = 1;
	return (interactive_or_not);
}
