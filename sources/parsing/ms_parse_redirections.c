/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:46:46 by jcervoni          #+#    #+#             */
/*   Updated: 2022/06/23 14:11:46 by aweaver          ###   ########.fr       */
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

t_arg	*ft_get_infile(t_arg *arg, t_arg *head)
{
	t_arg	*temp;
	char	*tmp;

	if (arg->token == TOKEN_INFILE && arg->content[0] == '<'
		&& ft_strlen(arg->content) > 1)
	{
		tmp = ft_strdup(&arg->content[1]);
		arg->content = ft_magic_malloc(FREE, 0, arg->content);
		arg->content = tmp;
	}
	else if (arg->token == TOKEN_INFILE && arg->content[0] == '<'
		&& ft_strlen(arg->content) == 1)
	{
		if (arg->next == NULL || arg->next->token != TOKEN_CMD)
		{
			ft_clear_and_quit(arg->next, head);
			return (NULL);
		}
		temp = arg->next;
		temp->token = TOKEN_INFILE;
		return (temp);
	}
	return (arg);
}

/* ************************************************************************** */
/*	ACT : same as previous with HEREDOC token;                                */
/*	ARG : a t_arg element                                                     */
/*	RET : a pointer to a t_arg element                                        */
/* ************************************************************************** */

t_arg	*ft_get_heredoc(t_arg *arg, t_arg *head)
{
	t_arg	*temp;
	char	*tmp;

	if (arg->token == TOKEN_HEREDOC && arg->content[0] == '<'
		&& ft_strlen(arg->content) > 2)
	{
		tmp = ft_strdup(&arg->content[2]);
		arg->content = ft_magic_malloc(FREE, 0, arg->content);
		arg->content = tmp;
	}
	else if (arg->token == TOKEN_HEREDOC && arg->content[0] == '<'
		&& ft_strlen(arg->content) == 2)
	{
		if (arg->next == NULL || arg->next->token != TOKEN_CMD)
		{
			ft_clear_and_quit(arg->next, head);
			return (NULL);
		}
		temp = arg->next;
		temp->token = TOKEN_HEREDOC;
		return (temp);
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

t_arg	*ft_get_outfile(t_arg *arg, t_arg *head)
{
	t_arg	*temp;
	char	*tmp;

	if (arg->token == TOKEN_OUTFILE && arg->content[0] == '>'
		&& ft_strlen(arg->content) > 1)
	{
		tmp = ft_strdup(&arg->content[1]);
		arg->content = ft_magic_malloc(FREE, 0, arg->content);
		arg->content = tmp;
	}
	else if (arg->token == TOKEN_OUTFILE && arg->content[0] == '>'
		&& ft_strlen(arg->content) == 1)
	{
		if (arg->next == NULL || arg->next->token != TOKEN_CMD)
		{
			ft_clear_and_quit(arg->next, head);
			return (NULL);
		}
		temp = arg->next;
		temp->token = TOKEN_OUTFILE;
		return (temp);
	}
	return (arg);
}

/* ************************************************************************** */
/*	ACT : same as previous with APPENDOUT token;                              */
/*	ARG : a t_arg element                                                     */
/*	RET : a pointer to a t_arg element                                        */
/* ************************************************************************** */

t_arg	*ft_get_appendout(t_arg *arg, t_arg *head)
{
	t_arg	*temp;
	char	*tmp;

	if (arg->token == TOKEN_APPENDOUT && arg->content[0] == '>'
		&& ft_strlen(arg->content) > 2)
	{
		tmp = ft_strdup(&arg->content[2]);
		arg->content = ft_magic_malloc(FREE, 0, arg->content);
		arg->content = tmp;
	}
	else if (arg->token == TOKEN_APPENDOUT && arg->content[0] == '>'
		&& ft_strlen(arg->content) == 2)
	{
		if (arg->next == NULL || arg->next->token != TOKEN_CMD)
		{
			ft_clear_and_quit(arg->next, head);
			return (NULL);
		}
		temp = arg->next;
		temp->token = TOKEN_APPENDOUT;
		return (temp);
	}
	return (arg);
}
