/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:09:57 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/11 17:12:37 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*	ACT : check if opened quote is closed, create a t_arg element, add it     */
/*		in queue of the list and return a pointer to the list                 */
/*	ARG : terminal input formated as char *, input index, t_arg list          */
/*	RET : t_arg element, NULL in case of error                                */
/* ************************************************************************** */

t_arg	*ft_get_dquote_arg(char *input, int *i, t_arg *arg)
{
	t_arg	*new;
	char	*sub;
	int		j;

	j = 0;
	new = NULL;
	sub = NULL;
	if (input[j] != '\0')
	{
		if (input[j] == '"')
			while (input[++j] != '"' && input[j] != '\0' && input[j] != '|')
				;
		if (input[++j] == ' ')
			sub = ft_substr(input, 0, j + 1);
		else if (input[j + 1] != '\0')
			while (input[++j] != '\0' && input[j] != ' ')
				;
	}
	sub = ft_substr(input, 0, j);
	if (sub == NULL)
		return (NULL);
	new = ft_newarg(sub);
	ft_addarg_back(&arg, new);
	*i += ft_strlen(new->content);
	return (arg);
}

int	ft_remove_dquotes(t_arg *arg)
{
	char	*temp;
	char	*to_copy;
	int		i;
	int		st;

	i = -1;
	st = 0;
	to_copy = "";
	while (arg->content[++i] != '\0')
	{
		if (arg->content[i] == '"')
		{
			if (i == 0)
				st = 1;
			if (i > st)
			{
				temp = ft_substr(arg->content, st, i - st);
				to_copy = ft_strjoin(to_copy, temp);
				free(temp);
				st = i + 1;
			}
		}
	}
	arg->content = to_copy;
	return (0);
}

int	ft_check_dquotes(t_arg *arg)
{
	int	i;
	int	dq;

	i = 0;
	dq = 0;
	while (arg->content[i] != '\0')
	{
		if (arg->content[i] == '"')
			dq++;
		i++;
	}
	if ((dq != 0 && dq % 2 != 0) || dq == 0)
		return (-1);
	return (0);
}
