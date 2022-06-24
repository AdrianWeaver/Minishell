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

int	ft_clear_and_quit(t_arg *arg, t_arg *head, t_env *env)
{
	if (arg == NULL)
		printf("minishell: syntax error near unexpected token `newline\'\n");
	else if (arg->token == TOKEN_INFILE)
		printf("minishell: syntax error near unexpected token `<\'\n");
	else if (arg->token == TOKEN_HEREDOC)
		printf("minishell: syntax error near unexpected token `<<\'\n");
	else if (arg->token == TOKEN_OUTFILE)
		printf("minishell: syntax error near unexpected token `>\'\n");
	else if (arg->token == TOKEN_APPENDOUT)
		printf("minishell: syntax error near unexpected token `>>\'\n");
	else if (arg->token == TOKEN_PIPE)
		printf("minishell: syntax error near unexpected token `|\'\n");
	ft_clear_arg(head);
	ft_free_env(env);
	exit(0);
}
