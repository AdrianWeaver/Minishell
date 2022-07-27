/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:25:05 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/27 12:37:57 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_manage_heredoc(t_arg *arg, t_env *env, int i, int std[2])
{
	char	*secret_name;
	char	*name_end;

	secret_name = NULL;
	dup2(std[0], STDIN_FILENO);
	name_end = ft_itoa(i);
	ft_magic_malloc(ADD, 0, name_end);
	secret_name = ft_strjoin("/tmp/.MiNiShElL#@tmp", name_end);
	ft_magic_malloc(ADD, 0, secret_name);
	if (arg->content[0] == '<')
		arg = arg->next;
	ft_heredoc(arg, env, std, secret_name);
	i--;
	arg = arg->next;
	return (secret_name);
}

int	ft_redir_heredoc(t_arg *arg, t_env *env, int i, int std[2])
{
	char	*heredoc_file;
	int		hd_fd;

	heredoc_file = NULL;
	hd_fd = -1;
	heredoc_file = ft_manage_heredoc(arg, env, i, std);
	if (heredoc_file != NULL)
	{
		hd_fd = open(heredoc_file, O_RDONLY);
		unlink(heredoc_file);
		dup2(hd_fd, STDIN_FILENO);
	}
	return (hd_fd);
}
