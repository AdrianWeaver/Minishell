/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitch <mitch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:32:14 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/16 19:01:18 by mitch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirection(t_arg *arg)
{
	int	fd;

	if (arg->token == TOKEN_OUTFILE || arg->token == TOKEN_APPENDOUT)
		fd = ft_redirection_out(arg);
	else if (arg->token == TOKEN_INFILE)
		fd = ft_redirection_in(arg);
	return (fd);
}

int	ft_redirection_out(t_arg *arg)
{
	int	fd;

	if (arg->token == TOKEN_OUTFILE)
		fd = open(arg->content, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (arg->token == TOKEN_APPENDOUT)
		fd = open(arg->content, O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	return (fd);
}

int	ft_redirection_in(t_arg *arg)
{
	int	fd;

	if (arg->token == TOKEN_INFILE)
		fd = open(arg->content, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	return (fd);
}

void	ft_get_redirections(t_arg *arg)
{
	t_arg	*head;

	head = arg;
	while (arg)
	{
		arg = ft_get_infile(arg, head);
		arg = ft_get_heredoc(arg, head);
		arg = ft_get_outfile(arg, head);
		arg = ft_get_appendout(arg, head);
		ft_check_double_pipe(arg, head);
		arg = arg->next;
	}
}
