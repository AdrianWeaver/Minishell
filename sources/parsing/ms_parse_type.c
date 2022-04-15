/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:46:46 by jcervoni          #+#    #+#             */
/*   Updated: 2022/04/15 17:22:47 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*	ACT : check arg's token, if INFILE, keep only file's name if len > 1,     */
/*		else will replace next element's token by INFILE, delete current      */
/*		element and will return a pointer to the next element. Do nothing in  */
/*		any other case                                                        */
/*	ARG : a t_arg element                                                     */
/*	RET : a pointer to a t_arg element                                        */
/* ************************************************************************** */

t_arg	*ft_get_infile(t_arg *arg)
{
	t_arg	*temp;

	if (arg->token == TOKEN_INFILE && ft_strlen(arg->content) > 1)
			arg->content = &arg->content[1];
	else if (arg->token == TOKEN_INFILE && ft_strlen(arg->content) == 1)
	{
		if (arg->next->token == TOKEN_INFILE)
		{
			printf("erreur de syntaxe pres du symbole inattendu ' < '\n");
			exit (1);
		}
		else
		{
			temp = arg->next;
			temp->token = TOKEN_INFILE;
			return (temp);
		}
	}
	return (arg);
}

/* ************************************************************************** */
/*	ACT : same as previous with HEREDOC token;                                */
/*	ARG : a t_arg element                                                     */
/*	RET : a pointer to a t_arg element                                        */
/* ************************************************************************** */

t_arg	*ft_get_heredoc(t_arg *arg)
{
	t_arg	*temp;

	if (arg->token == TOKEN_HEREDOC && ft_strlen(arg->content) > 2)
		arg->content = &arg->content[2];
	else if (arg->token == TOKEN_HEREDOC && ft_strlen(arg->content) == 2)
	{
		if (arg->next->token == TOKEN_HEREDOC)
		{
			printf("erreur de syntaxe pres du symbole inattendu ' << '\n");
			exit (1);
		}
		else
		{
			temp = arg->next;
			temp->token = TOKEN_HEREDOC;
			return (temp);
		}
	}
	return (arg);
}

/* ************************************************************************** */
/*	ACT : check arg's token, if OUTFILE, keep only file's name if len > 1,    */
/*		else will replace next element's token by OUTFILE, delete current     */
/*		element and will return a pointer to the next element. Do nothing in  */
/*		any other case                                                        */
/*	ARG : a t_arg element                                                     */
/*	RET : a pointer to a t_arg element                                        */
/* ************************************************************************** */

t_arg	*ft_get_outfile(t_arg *arg)
{
	t_arg	*temp;

	if (arg->token == TOKEN_OUTFILE && ft_strlen(arg->content) > 1)
			arg->content = &arg->content[1];
	else if (arg->token == TOKEN_OUTFILE && ft_strlen(arg->content) == 1)
	{
		if (arg->next->token == TOKEN_OUTFILE)
		{
			printf("erreur de syntaxe pres du symbole inattendu ' < '\n");
			exit (1);
		}
		else
		{
			temp = arg->next;
			temp->token = TOKEN_OUTFILE;
			return (temp);
		}
	}
	return (arg);
}

/* ************************************************************************** */
/*	ACT : same as previous with APPENDOUT token;                              */
/*	ARG : a t_arg element                                                     */
/*	RET : a pointer to a t_arg element                                        */
/* ************************************************************************** */

t_arg	*ft_get_appendout(t_arg *arg)
{
	t_arg	*temp;

	if (arg->token == TOKEN_APPENDOUT && ft_strlen(arg->content) > 2)
		arg->content = &arg->content[2];
	else if (arg->token == TOKEN_APPENDOUT && ft_strlen(arg->content) == 2)
	{
		if (arg->next->token == TOKEN_APPENDOUT)
		{
			printf("erreur de syntaxe pres du symbole inattendu ' << '\n");
			exit (1);
		}
		else
		{
			temp = arg->next;
			temp->token = TOKEN_APPENDOUT;
			return (temp);
		}
	}
	return (arg);
}
