/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:09:57 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/17 17:51:18 by jcervoni         ###   ########.fr       */
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

int	ft_remove_dquotes(t_arg *arg, int *dq_nbr)
{
	char	*temp;
	char	*to_copy;
	int		i;
	int		j;
	int		st;

	i = -1;
	st = 0;
	j = 1;
	to_copy = "";
	while (arg->content[++i] != '\0')
	{
		if (j <= dq_nbr[0] && i == dq_nbr[j])
		{
			if (i == 0)
				st = 1;
			if (i > st)
			{
				temp = ft_substr(&arg->content[st], 0, i - st);
				to_copy = ft_strjoin(to_copy, temp);
				// free(temp);
				st = i + 1;
			}
			j++;
		}
		else if (j > dq_nbr[0])
		{
			while (arg->content[i])
				i++;
			temp = ft_substr(arg->content, st, i - (st));
			to_copy = ft_strjoin(to_copy, temp);
			// free(temp);
		}
	}
	arg->content = ft_strdup(to_copy);
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
	int		ret;

	i = 0;
	j = 1;
	ret = 0;
	while (arg->content[i] != '\0')
	{
		if (arg->content[i] == '"')
		{
			dq_nbr[j] = dq_nbr[j] + i - ret;
			j++;
		}
		if (arg->content[i] == '$' && ft_set_dq_jump(&arg->content[i + 1]) > 0)
		{
			if (ft_check_var(&arg->content[i], env) > 0)
				dq_nbr[j] += ft_expand_size(&arg->content[i + 1], env) - 1;
			else
				ret += ft_set_dq_jump(&arg->content[i + 1]) + 1;
		}
		i++;
	}
}

int	ft_test(t_arg *arg, t_env *env)
{
	int		*dq;
	char	*flags;
	char	**pieces;

	pieces = ft_count_expand(arg, env);
	dq = ft_count_dquotes(arg);
	if (!dq || !pieces)
		return (-1);
	ft_set_final_dq_index(arg, dq, env);
	flags = ft_get_var_pos(arg->content, env);
	ft_final_string(arg, pieces, flags, env);
	printf("flags = %s\n", flags);
	ft_remove_dquotes(arg, dq);
	return (0);
}

int	ft_set_dq_jump(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]) == 1 || str[i] == '_')
		i++;
	return (i);
}
