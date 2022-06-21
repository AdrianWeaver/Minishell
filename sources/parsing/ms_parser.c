/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:10:13 by jcervoni          #+#    #+#             */
/*   Updated: 2022/06/15 06:37:01 by jcervoni         ###   ########.fr       */
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
		else if (temp->content[0] == '<' && temp->content[1] != '<')
			temp->token = TOKEN_INFILE;
		else if (temp->content[0] == '<' && temp->content[1] == '<')
			temp->token = TOKEN_HEREDOC;
		else if (temp->content[0] == '>' && temp->content[1] != '>')
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
			{
				// if (input[i] == '<')
				// 	arg = ft_get_redir_in_arg(&input[i], &i, arg);
				// else
					arg = ft_get_arg(&input[i], &i, arg);
			}
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
	free(sub);
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
		free(sub);
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
	free(sub);
	return (arg);
}

// t_arg *ft_get_redir_in_arg(char *str, int *i, t_arg *arg)
// {
// 	t_arg	*new;
// 	int		j;
// 	int		st;
// 	char	*sub;

// 	j = 0;
// 	st = 0;
// 	new = NULL;
// 	while (str[j] == '<')
// 		j++;
// 	// if (j > 1)
// 	// 	ft_error;
// 	while (str[j] && str[j] == ' ')
// 		j++;
// 	while (str[j] && str[j] != ' ')
// 		j++;
// }
