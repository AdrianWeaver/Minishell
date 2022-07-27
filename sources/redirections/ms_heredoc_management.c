/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:25:05 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/27 12:38:51 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_manage_heredoc(t_arg *arg, t_env *env, int std[2])
{
	char	*heredoc_name;

	heredoc_name = NULL;
	heredoc_name = ft_heredoc(arg, env, std);
	arg->content = ft_magic_malloc(FREE, 0, arg->content);
	arg->content = ft_strdup(heredoc_name);
	ft_magic_malloc(ADD, 0, arg->content);
	return (heredoc_name);
}

int	ft_redir_heredoc(t_arg *arg, t_env *env, int std[2])
{
	while (arg)
	{
		if (arg->token == TOKEN_HEREDOC)
		{
			if (arg->content[0] == '<')
			arg = arg->next;
			if (ft_manage_heredoc(arg, env, std) == NULL)
				return (-1);
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
		secret_name = ft_strjoin("/tmp/.MiNiShElL#@tmp", name_end);
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
