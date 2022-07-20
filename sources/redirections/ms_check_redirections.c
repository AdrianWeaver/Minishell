/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:02:08 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/20 10:03:14 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_first_arg(t_arg *arg)
{
	char	*tok;

	tok = NULL;
	if (arg && arg->token == TOKEN_PIPE)
		tok = "|";
	else if (arg && arg->token == TOKEN_AND)
		tok = "&&";
	else if (arg && arg->content[0] == '(')
		tok = "(";
	if (tok)
	{
		ft_eprintf("%s `%s\'\n", SYNTAX_ERROR, tok);
		return (1);
	}
	return (0);
}

int	ft_check_wrong_arg(t_arg *arg)
{
	char	*tok;

	tok = NULL;
	if (arg && arg->token == TOKEN_AND)
		tok = "&&";
	else if (arg && arg->content[0] == '(')
		tok = "(";
	if (tok)
	{
		ft_eprintf("%s `%s\'\n", SYNTAX_ERROR, tok);
		return (1);
	}
	return (0);
}

int	ft_get_redirections(t_arg *arg)
{
	t_arg	*head;

	head = arg;
	if (ft_check_first_arg(arg) == 1)
		return (1);
	while (arg)
	{
		if (ft_check_wrong_arg(arg) == 1)
			return (1);
		if (ft_check_double_redir(arg) != 0 || ft_check_single_redir(arg) != 0)
			return (1);
		ft_set_redirections(arg, head);
		arg = arg->next;
	}
	return (0);
}
