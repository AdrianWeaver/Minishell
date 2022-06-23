/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:55:48 by jcervoni          #+#    #+#             */
/*   Updated: 2022/06/23 14:07:30 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*	ACT : check is char given is a bash operator                              */
/*	ARG : each char from the input                                            */
/*	RET : 1 if c is an operator, 0 if not                                     */
/* ************************************************************************** */

int	ft_check_op(char c)
{
	if (c != '\0')
	{
		if (c == '|' || c == '<' || c == '>')
			return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*	ACT : check is char given is a quote delimiter                            */
/*	ARG : each char from the input                                            */
/*	RET : 1 if c is an delimiter, 0 if not                                    */
/* ************************************************************************** */

int	ft_check_arg(char c)
{
	if (c == '|' || c == ' ' || c == '\0')
		return (1);
	return (0);
}
/* ************************************************************************** */
/*	ACT : calculate length of char to jump ahaed in case of wrong $VAR name   */
/*	ARG : pointer to an occurence of wrong $VAR name                          */
/*	RET : length to add to dquote's position                                  */
/* ************************************************************************** */

int	ft_set_q_jump(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	return (i);
}

/* ************************************************************************** */
/*	ACT : check if an $ENV_VAR with name given in param exists                */
/*	ARG : string name, a pointer to a t_env struct                            */
/*	RET : 0 if $ENV_VAR exists, -1 if not                                     */
/* ************************************************************************** */

int	ft_check_env_var(char *str, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strcmp(str, temp->name) == 0)
			return (0);
		temp = temp->next;
	}
	return (-1);
}

/* ************************************************************************** */
/*	ACT : for each char '$', check if $string is an existing env var name     */
/*	ARG : string input, a pointer to a t_env struct                           */
/*	RET : lenght of var's name if $ENV_VAR exists, -1 if not                  */
/* ************************************************************************** */

int	ft_check_var(char *str, t_env *env)
{
	char	*sub;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str[i] == '$' && str[i + 1])
	{
		i++;
		j = i;
		while (str[i] && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
			i++;
		sub = ft_substr(str, j, i - j);
		if (!sub)
			return (-1);
		if (ft_check_env_var(sub, env) == 0)
		{
			sub = ft_magic_malloc(FREE, 0, sub);
			return (i - j);
		}
		sub = ft_magic_malloc(FREE, 0, sub);
	}
	return (-1);
}
