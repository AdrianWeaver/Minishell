/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:15:00 by jcervoni          #+#    #+#             */
/*   Updated: 2022/04/15 10:42:27 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_clear_and_quit(t_arg *arg, t_arg *head)
{
	if (arg == NULL)
		ft_eprintf("minishell: syntax error near unexpected token `newline\'\n"
			);
	else if (arg->token == TOKEN_INFILE)
		ft_eprintf("minishell: syntax error near unexpected token `<\'\n");
	else if (arg->token == TOKEN_HEREDOC)
		ft_eprintf("minishell: syntax error near unexpected token `<<\'\n");
	else if (arg->token == TOKEN_OUTFILE)
		ft_eprintf("minishell: syntax error near unexpected token `>\'\n");
	else if (arg->token == TOKEN_APPENDOUT)
		ft_eprintf("minishell: syntax error near unexpected token `>>\'\n");
	else if (arg->token == TOKEN_PIPE)
		ft_eprintf("minishell: syntax error near unexpected token `|\'\n");
	ft_clear_arg(head);
	ft_magic_malloc(FLUSH, 0, NULL);
	exit(0);
}

int	ft_check_redir(t_arg *arg)
{
	int	i;

	i = 0;
	if (arg->token == TOKEN_HEREDOC)
	{
		while (arg->content[i] == '<')
			i++;
		if ( i > 2)
			printf("minishell: syntax error near unexpected token `%c\'\n"
				, arg->content[i]);
	}
	else if (arg->token == TOKEN_APPENDOUT)
	{
		while (arg->content[i] == '>')
			i++;
		if (i > 2)
			printf("minishell: syntax error near unexpected token `%c\'\n"
				, arg->content[i]);
	}
	if (i > 2)
		return (1);
	return (0);
}