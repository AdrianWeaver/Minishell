/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:51:25 by jcervoni          #+#    #+#             */
/*   Updated: 2022/06/23 13:51:44 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo_n_opt(t_arg *arg)
{
	int		n_opt;
	size_t	i;

	n_opt = 0;
	i = 1;
	if (arg && arg->content[0] == '-')
	{
		while (arg->content[i] && arg->content[i] == 'n')
			i++;
		if (i == ft_strlen(arg->content))
			n_opt = 1;
	}
	return (n_opt);
}

t_arg	*ft_echo_skip_opt(t_arg *arg, int *n_opt)
{
	while (arg)
	{
		if (ft_echo_n_opt(arg) == 1)
		{
			arg = arg->next;
			*n_opt = 1;
		}
		else
			break ;
	}
	return (arg);
}

int	ft_echo(t_arg *arg)
{
	char	*to_print;
	int		n_opt;

	n_opt = 0;
	arg = ft_echo_skip_opt(arg, &n_opt);
	to_print = ft_calloc(1, 1);
	while (arg && arg->token == TOKEN_CMD)
	{
		to_print = ft_strjoin_free(to_print, arg->content);
		if (arg->next && arg->next->token == TOKEN_CMD)
			to_print = ft_strjoin_free(to_print, " ");
		arg = arg->next;
	}
	if (n_opt == 0)
		to_print = ft_strjoin_free(to_print, "\n");
	printf("echo returns %s", to_print);
	to_print = ft_magic_malloc(FREE, 0, to_print);
	return (0);
}
