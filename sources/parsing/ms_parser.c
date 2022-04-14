/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:10:13 by jcervoni          #+#    #+#             */
/*   Updated: 2022/04/14 16:44:31 by jcervoni         ###   ########.fr       */
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
		if (ft_isalnum(temp->content[0]) == 1)
			temp->token = "word";
		else if (temp->content[0] == '|')
			temp->token = "pipe";
		else if (temp->content[0] == '<')
			temp->token = "input";
		else if (temp->content[0] == '>')
			temp->token = "output";
		else if (temp->content[0] == '\'')
			temp->token = "quote";
		else if (temp->content[0] == '"')
			temp->token = "dquote";
		else
		{
			temp->token = NULL;
			return (1);
		}
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
	int		j;

	i = -1;
	arg = NULL;
	while (input[++i] != '\0')
	{
		while (input[i] != ' ' && input[i] != '\0')
		{
			j = i;
			if (ft_check_quotes(input[i]) == 1)
				arg = ft_get_quote_arg(&input[i], &i, arg);
			else
				arg = ft_get_arg(&input[j], &i, arg);
			i++;
		}
	}
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
	while (ft_check_quotes(input[j]) != 1
		&& input[j] != '\0' && input[j] != ' ')
		j++;
	sub = ft_substr(input, 0, j);
	if (sub == NULL)
		return (NULL);
	new = ft_newarg(sub);
	ft_addarg_back(&arg, new);
	*i += ft_strlen(new->content);
	return (arg);
}

/* ************************************************************************** */
/*	ACT : check if opened quote is closed, create a t_arg element, add it     */
/*		in queue of the list and return a pointer to the list                 */
/*	ARG : terminal input formated as char *, input index, t_arg list          */
/*	RET : t_arg element, NULL in case of error                                */
/* ************************************************************************** */

t_arg	*ft_get_quote_arg(char *input, int *i, t_arg *arg)
{
	t_arg	*new;
	char	*sub;
	int		j;

	j = 0;
	new = NULL;
	if (input[j] != '\0')
	{
		if (input[j] == '"')
			while (input[++j] != '"' && input[j] != '\0')
				;
		else if (input[j] == '\'')
			while (input[++j] != '\'' && input[j] != '\0')
				;
		if (input[j] != '\0')
			sub = ft_substr(input, 0, j + 1);
	}
	if (sub == NULL)
		return (NULL);
	new = ft_newarg(sub);
	ft_addarg_back(&arg, new);
	*i += ft_strlen(new->content);
	return (arg);
}

/* ************************************************************************** */
/*	ACT : check if char is ' or "                                             */
/*	ARG : a char                                                              */
/*	RET : 1 if quote is found, 0 if not                                       */
/* ************************************************************************** */

int	ft_check_quotes(char input)
{
	if (input == '\'' || input == '"')
		return (1);
	return (0);
}
