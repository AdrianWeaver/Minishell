/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:10:13 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/18 12:05:53 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*	ACT : set token type for each element of the terminal input               */
/*	ARG : the terminal input formated as a char *                             */
/*	RET : 0 if all good; 1 in case of error                                   */
/* ************************************************************************** */

int	ft_check_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
int	ft_set_token(t_arg *args)
{
	t_arg	*temp;

	temp = args;
	while (temp != NULL)
	{	
		if (temp->content[0] == '|')
			temp->token = TOKEN_PIPE;
		else if (temp->content[0] == '<' && temp->content[1] != '<')
			temp->token = TOKEN_INFILE;
		else if (temp->content[0] == '<' && temp->content[1] == '<')
			temp->token = TOKEN_HEREDOC;
		else if (temp->content[0] == '>' && temp->content[1] != '>')
			temp->token = TOKEN_OUTFILE;
		else if (temp->content[0] == '>' && temp->content[1] == '>')
			temp->token = TOKEN_APPENDOUT;
		else if (temp->content[0] == '\'')
			temp->token = TOKEN_QUOTE;
		else if (temp->content[0] == '"')
			temp->token = TOKEN_DQUOTE;
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
	int		j;

	i = 0;
	arg = NULL;
	while (input[i] != '\0')
	{
		if (input[i] != ' ' && input[i] != '\0')
		{
			j = i;
			if (input[i] == '"')
				arg = ft_get_dquote_arg(&input[j], &i, arg);
			else
				arg = ft_get_arg(&input[j], &i, arg);
		}
		else if (input[i] == ' ')
			i++;
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
	if (input[j] == '|')
	{
		sub = "|";
		new = ft_newarg(sub);
		ft_addarg_back(&arg, new);
		*i += ft_strlen(new->content);
		j++;
		return (arg);
	}
	while (input[j] != '\0' && input[j] != ' ' && input[j] != '|')
		j++;
	sub = ft_substr(input, 0, j);
	if (sub == NULL)
		return (NULL);
	new = ft_newarg(sub);
	ft_addarg_back(&arg, new);
	*i += ft_strlen(new->content);
	return (arg);
}

void	ft_join_cmd(t_arg *arg)
{
	t_arg	*temp;
	char	*space;
	int		sec;

	space = " ";
	sec = 0;
	temp = arg->next;
	while (temp != NULL && arg->token == TOKEN_CMD && temp->content[0] == '-')
	{
		if (sec == 0)
		{
			arg->content = ft_strjoin(arg->content, space);
			arg->content = ft_strjoin(arg->content, temp->content);
			sec = 1;
		}
		else if (sec == 1)
			arg->content = ft_strjoin(arg->content, &temp->content[1]);
		if (temp->next != NULL)
			arg->next = temp->next;
		else
			arg->next = NULL;
		free(temp);
		temp = arg->next;
	}
}
