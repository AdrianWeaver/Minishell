/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:32:14 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/28 18:07:34 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_redirection(t_arg *arg)
{
	int	fd;
	int	*currents;

	fd = 0;
	currents = ft_set_currents();
	while (arg && arg->token != TOKEN_PIPE)
	{
		if (arg->content[0] == '>' || arg->content[0] == '<')
				arg = arg->next;
		if (arg->token == TOKEN_OUTFILE || arg->token == TOKEN_APPENDOUT)
		{
			fd = ft_redirection_out(arg, currents[1]);
			currents[1] = fd;
		}
		else if (arg->token == TOKEN_INFILE || arg->token == TOKEN_HEREDOC)
		{
			fd = ft_redirection_in(arg, currents[0]);
			currents[0] = fd;
		}
		if (currents[0] < 0 || currents[1] < 0)
			break ;
		arg = arg->next;
	}
	return (currents);
}

int	ft_redirection_out(t_arg *arg, int current_out)
{
	int	fd;

	if (arg->token == TOKEN_OUTFILE)
		fd = open(arg->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (arg->token == TOKEN_APPENDOUT)
		fd = open(arg->content, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return (ft_eprintf("%s: %s\n", strerror(errno), arg->content), -1);
	if (current_out > 1)
		close(current_out);
	if (access(arg->content, F_OK) != 0)
		return (ft_eprintf("%s: %s\n", strerror(errno), arg->content), -1);
	dup2(fd, STDOUT_FILENO);
	return (fd);
}

int	ft_redirection_in(t_arg *arg, int current_in)
{
	int	fd;

	ft_eprintf("arg = %s\n", arg->content);
	if (arg->token == TOKEN_INFILE)
	{
		fd = open(arg->content, O_RDWR);
		if (fd == -1)
			return (ft_eprintf("%s: %s\n", strerror(errno), arg->content), -1);
	}
	else if (arg->token == TOKEN_HEREDOC)
	{
		fd = open(arg->content, O_RDWR);
		if (fd == -1)
			return (ft_eprintf("%s: %s\n", strerror(errno), arg->content), -1);
		unlink(arg->content);
	}
	if (current_in > 0)
		close(current_in);
	dup2(fd, STDIN_FILENO);
	return (fd);
}

int	ft_set_redirections(t_arg *arg, t_arg *head)
{
	arg = ft_get_infile(arg, head);
	if (arg == NULL)
		return (1);
	arg = ft_get_heredoc(arg, head);
	if (arg == NULL)
		return (1);
	arg = ft_get_outfile(arg, head);
	if (arg == NULL)
		return (1);
	arg = ft_get_appendout(arg, head);
	if (arg == NULL)
		return (1);
	if (ft_check_double_pipe(arg, head) == 1)
		return (1);
	return (0);
}

int	*ft_set_currents(void)
{
	int	*currents;

	currents = ft_magic_malloc(MALLOC, sizeof(int) * 2, NULL);
	currents[0] = 0;
	currents[1] = 1;
	return (currents);
}
