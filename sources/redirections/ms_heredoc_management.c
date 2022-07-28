/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:25:05 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/28 18:00:07 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_manage_heredoc(t_arg *arg, t_env *env, int std[2], char **heredoc_name)
{
	int	heredoc_status;

	heredoc_status = ft_heredoc(arg, env, std, heredoc_name);
	if (heredoc_status != 0)
		return (heredoc_status);
	arg->content = ft_magic_malloc(FREE, 0, arg->content);
	arg->content = ft_strdup(*heredoc_name);
	ft_magic_malloc(ADD, 0, arg->content);
	return (0);
}

int	ft_redir_heredoc(t_arg *arg, t_env *env, int std[2], char **heredoc_name)
{
	int	heredoc_return;

	while (arg)
	{
		if (arg->token == TOKEN_HEREDOC)
		{
			if (arg->content[0] == '<')
			arg = arg->next;
			heredoc_return = ft_manage_heredoc(arg, env, std, heredoc_name);
			if (heredoc_return != 0)
				return (heredoc_return);
		}
		arg = arg->next;
	}
	return (0);
}

char	*ft_create_heredoc(void)
{
	char	*secret_name;
	char	*name_end;
	int		i;

	i = INT_MAX;
	secret_name = NULL;
	while (1)
	{
		name_end = ft_itoa(i);
		ft_magic_malloc(ADD, 0, name_end);
		secret_name = ft_strjoin("/tmp/.MiNiShElL@#tmp", name_end);
		ft_magic_malloc(ADD, 0, secret_name);
		if (access(secret_name, F_OK) == -1)
			break ;
		name_end = ft_magic_malloc(FREE, 0, name_end);
		secret_name = ft_magic_malloc(FREE, 0, secret_name);
		i--;
		if (i == INT_MAX)
			return (NULL);
	}
	return (secret_name);
}
