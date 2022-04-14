/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:10:13 by jcervoni          #+#    #+#             */
/*   Updated: 2022/04/14 11:33:20 by jcervoni         ###   ########.fr       */
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
			temp->token = ft_strdup("word");
		else if (temp->content[0] == '|')
			temp->token = ft_strdup("pipe");
		else if (temp->content[0] == '<')
			temp->token = ft_strdup("input");
		else if (temp->content[0] == '>')
			temp->token = ft_strdup("output");
		else if (temp->content[0] == '\'')
			temp->token = ft_strdup("quote");
		else if (temp->content[0] == '"')
			temp->token = ft_strdup("dquote");
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

	i = -1;
	arg = NULL;
	while (input[++i] != '\0')
	{
		while (input[i] != ' ' && input[i] != '\0')
		{
			j = i;
			if (ft_check_quotes(input[i]) == 1)
			{
				temp = ft_get_quote_arg(&input[i]);
				ft_addarg_back(&arg, temp);
				i += ft_strlen(temp->content);
			}
			else
			{
				while (ft_check_quotes(input[i]) != 1 && input[i] != '\0' && input[i] != ' ')
					i++;
				sub = ft_substr(&input[j], 0, i - j);
				temp = ft_newarg(sub);
				ft_addarg_back(&arg, temp);
			}
		}
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

t_arg	*ft_get_quote_arg(char *input)
{
	t_arg	*arg;
	char	*sub;
	int		i;

	i = 0;
	if (input[i] != '\0')
	{
		if (input[i] == '"')
		{
			i++;
			while (input[i] != '"' && input[i] != '\0')
				i++;
			if (input[i] == '\0')
				return (NULL);
			sub = ft_substr(input, 0, i + 1);
		}
		else if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'' && input[i] != '\0')
				i++;
			if (input[i] == '\0')
				return (NULL);
			sub = ft_substr(input, 0, i + 1);
		}
	}
	arg = ft_newarg(sub);
	return (arg);
}

int	ft_check_quotes(char input)
{
	if (input == '\'' || input == '"')
		return (1);
	return (0);
}
