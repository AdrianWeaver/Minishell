/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:09:57 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/12 16:28:31 by jcervoni         ###   ########.fr       */
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
			else if (i > st)
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

int	*ft_count_dquotes(t_arg *arg)
{
	int	i;
	int	dq;
	int	*dq_nbr;

	i = 0;
	dq = 0;
	while (arg->content[i] != '\0')
	{
		if (arg->content[i] == '"')
			dq++;
		i++;
	}
	if (dq != 0 && dq % 2 != 0)
		return (NULL);
	dq_nbr = calloc(sizeof(int), dq + 1);
	if (!dq_nbr)
		return (NULL);
	dq_nbr[0] = dq;
	return (dq_nbr);
}

void	ft_set_final_dq_index(t_arg *arg, int *dq_nbr, t_env *env)
{
	int		i;
	int		j;
	
	i = 0;
	j = 1;
	while (arg->content[i] != '\0')
	{
		if (arg->content[i] == '"')
		{
			dq_nbr[j] += i;
			printf("quote a l'index :%d\n", dq_nbr[j]);
			j++;
		}
		else if (arg->content[i] == '$' && (ft_isalnum(arg->content[i + 1]) == 1
			|| arg->content[i + 1] == '_'))
			{
				dq_nbr[j] += ft_expand_size(&arg->content[i + 1], env) - 1;
			}
		i++;	
	}
}

int	ft_test(t_arg *arg, t_env *env)
{
	int		*dq;
	char	**pieces;
	
	pieces = ft_count_expand(arg);
	dq = ft_count_dquotes(arg);
	if (!dq || !pieces)
		return (-1);
	ft_set_final_dq_index(arg, dq, env);
	ft_get_final_string(arg, pieces, env);
	return (0);
}
