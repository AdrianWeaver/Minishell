/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:10:13 by jcervoni          #+#    #+#             */
/*   Updated: 2022/04/13 16:03:35 by jcervoni         ###   ########.fr       */
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
		if (ft_isalpha(temp->content[0]) == 1)
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
			return (1);
		temp = temp->next;
	}
	return (0);
}

/* ************************************************************************** */
/*	ACT : create a t_arg list of each sequence from terminal input            */
/*	ARG : terminal input formated as char *                                   */
/*	RET : a pointer to the first element of a t_arg list                      */
/* ************************************************************************** */

t_arg	*ft_get_args(char *input)
{
	t_arg	*arg;
	t_arg	*temp;
	char	*sub;
	int		i;
	int		j;

	i = 0;
	arg = NULL;
	while (input[i] != '\0')
	{
		j = i;
		if (ft_get_quote_arg(&input[i]) != -1)
			i += ft_get_quote_arg(&input[i]);
		while (input[i] != ' ' && input[i] != '\0')
			i++;
		sub = ft_substr(&input[j], 0, i - j);
		temp = ft_newarg(sub);
		free(sub);
		ft_addarg_back(&arg, temp);
		while(input[i] == ' ' && input[i] != '\0')
			i++;
	}
	return (arg);
}

/* ************************************************************************** */
/*	ACT : check each block from input and modify index if there's quote or    */
/*		dquote to keep spaces inside quotes                                   */
/*	ARG : terminal input formated as char *                                   */
/*	RET : index of closing quote if quote was opened; 0 if no                 */
/*		quote; -1 if quote opened but not closed                              */
/* ************************************************************************** */

int	ft_get_quote_arg(char *input)
{
	int	i;
	
	i = 0;
	if (input[i] != '\0')
	{
		if (input[i] == '"')
		{
			i++;
			while (input[i] != '"' && input[i] != '\0')
				i++;
			if (input[i] == '\0')
				return (-1);
			return (i);
		}
		else if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'' && input[i] != '\0')
				i++;
			if (input[i] == '\0')
				return (-1);
			return (i);
		}
	}
	return (0);
}