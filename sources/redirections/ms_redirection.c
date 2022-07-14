/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:32:14 by jcervoni          #+#    #+#             */
/*   Updated: 2022/06/23 16:48:29 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirection(t_arg *arg)
{
	int	fd;

	if (arg->token == TOKEN_OUTFILE || arg->token == TOKEN_APPENDOUT)
		fd = ft_redirection_out(arg);
	else if (arg->token == TOKEN_INFILE || arg->token == TOKEN_HEREDOC)
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

int	*ft_save_std_fds(void)
{
	int	*std;

	std = ft_magic_malloc(MALLOC, sizeof(int) * 3, NULL);
	std[0] = dup(0);
	std[1] = dup(1);
	std[2] = dup(2);
	return (std);
}
