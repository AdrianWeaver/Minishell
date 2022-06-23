/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:10:13 by jcervoni          #+#    #+#             */
/*   Updated: 2022/06/23 14:21:08 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*	ACT : set token type for each element of the terminal input               */
/*	ARG : the terminal input formated as a char *                             */
/*	RET : 0 if all good; 1 in case of error                                   */
/* ************************************************************************** */

int	ft_set_token(t_arg *args)
{
	t_arg	*temp;

	temp = args;
	while (temp != NULL)
	{	
		if (temp->content[0] == '|')
			temp->token = TOKEN_PIPE;
		else if ((temp->content[0] == '<' && ft_strlen(temp->content) == 1)
			|| (temp->content[0] == '<' && temp->content[1] != '<'))
			temp->token = TOKEN_INFILE;
		else if (temp->content[0] == '<' && temp->content[1] == '<')
			temp->token = TOKEN_HEREDOC;
		else if ((temp->content[0] == '>' && ft_strlen(temp->content) == 1)
			|| (temp->content[0] == '>' && temp->content[1] != '>'))
			temp->token = TOKEN_OUTFILE;
		else if (temp->content[0] == '>' && temp->content[1] == '>')
			temp->token = TOKEN_APPENDOUT;
		else
			temp->token = TOKEN_CMD;
		temp = temp->next;
	}
	return (0);
}

/* ************************************************************************** */
/*	ACT : create a t_arg list of each argument from terminal input            */
/*	ARG : terminal input formated as char *                                   */
/*	RET : a pointer to the first element of a t_arg list                      */
/* ************************************************************************** */

t_arg	*ft_get_args(char *input)
{
	t_arg	*arg;
	int		i;

	i = 0;
	arg = NULL;
	while (input[i] != '\0')
	{
		while (input[i] != ' ' && input[i] != '\0')
		{	
			if (input[i] == '"' || input[i] == '\'')
				arg = ft_get_quote_arg(&input[i], &i, arg, input[i]);
			else if (input[i])
				arg = ft_get_arg(&input[i], &i, arg);
		}
		if (input[i] != '\0')
			i++;
	}
	return (arg);
}

/* ************************************************************************** */
/*	ACT : check if opened quote is closed, create a t_arg element, add it     */
/*		in queue of the list and return a pointer to the list                 */
/*	ARG : terminal input formated as char *, input index, t_arg list          */
/*	RET : t_arg element, NULL in case of error                                */
/* ************************************************************************** */

t_arg	*ft_get_quote_arg(char *input, int *i, t_arg *arg, char delim)
{
	t_arg	*new;
	char	*sub;
	int		j;

	j = 0;
	new = NULL;
	if (input[++j] != '\0')
	{
		while (input[j] && input[j] != delim)
			j++;
		while (input[++j] && input[j] != ' ' && ft_check_op(input[j]) == 0)
			;
	}
	sub = ft_substr(input, 0, j);
	if (!sub)
		return (NULL);
	new = ft_newarg(sub);
	ft_addarg_back(&arg, new);
	*i += ft_strlen(new->content);
	sub = ft_magic_malloc(FREE, 0, sub);
	return (arg);
}

/* ************************************************************************** */
/*	ACT : check for each non quote element from input, create a t_arg         */
/*		element, add it in queue of the list and return a pointer to the list */
/*	ARG : terminal input formated as char *, input index, t_arg list          */
/*	RET : t_arg element, NULL in case of error                                */
/* ************************************************************************** */

t_arg	*ft_get_arg(char *input, int *i, t_arg *arg)
{
	t_arg	*new;
	int		j;
	char	*sub;

	j = 0;
	new = NULL;
	if (input[j] == '|')
	{
		sub = ft_strdup("|");
		new = ft_newarg(sub);
		ft_addarg_back(&arg, new);
		*i += ft_strlen(new->content);
		sub = ft_magic_malloc(FREE, 0, sub);
		return (arg);
	}
	while (ft_check_arg(input[j]) == 0)
		j++;
	sub = ft_substr(input, 0, j);
	if (sub == NULL)
		return (NULL);
	new = ft_newarg(sub);
	ft_addarg_back(&arg, new);
	*i += ft_strlen(new->content);
	sub = ft_magic_malloc(FREE, 0, sub);
	return (arg);
}

int	ft_check_double_pipe(t_arg *arg, t_arg *head, t_env *env)
{
	if (arg->token == TOKEN_PIPE)
	{
		if (arg->next == NULL || arg->next->token == TOKEN_PIPE)
			ft_clear_and_quit(arg->next, head, env);
	}
	return (0);
}
