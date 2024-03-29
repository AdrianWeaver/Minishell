/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:10:13 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/27 11:34:17 by jcervoni         ###   ########.fr       */
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
		else if (temp->content[0] == '&'
			&& temp->content[1] && temp->content[1] == '&')
			temp->token = TOKEN_AND;
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
		while (input[i] != ' ' && input[i] != '\t' && input[i] != '\0')
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
		while (input[j] && input[j] != ' ' && input[j] != '\t'
			&& ft_check_op(input[j]) == 0)
			j++;
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
	j += ft_move_cursor(input, j);
	sub = ft_substr(input, 0, j);
	if (sub == NULL)
		return (NULL);
	new = ft_newarg(sub);
	ft_addarg_back(&arg, new);
	*i += ft_strlen(new->content);
	sub = ft_magic_malloc(FREE, 0, sub);
	return (arg);
}

int	ft_move_cursor(char *input, int j)
{
	char	delim;
	int		i;

	delim = '\0';
	i = j - 1;
	while (ft_check_arg(input[++i]) == 0)
	{
		if (ft_check_in_out(input[i]) == 1)
			while (input[i] && ft_check_in_out(input[i]) == 1)
				i++;
		if (input[i] && ft_check_quote(input[i]) == 1)
			delim = input[i];
		if (delim != '\0')
		{
			i++;
			while (input[i] && input[i] != delim)
				i++;
		}
		if (ft_check_arg(input[i]) == 1)
			return (i);
	}
	return (i);
}
