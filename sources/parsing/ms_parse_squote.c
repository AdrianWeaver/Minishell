/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_squote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:26:15 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/18 16:35:29 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*ft_get_squote_arg(char *input, int *i, t_arg *arg)
{
	t_arg	*new;
	char	*sub;
	int		j;

	j = 0;
	new = NULL;
	sub = NULL;
	if (input[j] != '\0')
	{
		j++;
		while (input[j] && input[j] != '\'')
			j++;
		while (input[j] && input[j] != ' ' && ft_check_operator(input[j]) == 0)
			j++;
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

int	ft_remove_squotes(t_arg *arg, int *sq_nbr)
{
	char	*temp;
	int		i;
	int		j;
	int		t;

	i = 0;
	j = 1;
	t = -1;
	temp = malloc(sizeof(char) * (ft_strlen(arg->content)));
	if (!temp)
		return (-1);
	while (arg->content[i] != '\0')
	{
		if (j <= sq_nbr[0] && i == sq_nbr[j])
			j++;
		else
			temp[++t] = arg->content[i];
		i++;
	}
	temp[++t] = '\0';
	free(arg->content);
	arg->content = ft_strdup(temp);
	free(temp);
	return (0);
}

int	*ft_count_squotes(t_arg *arg)
{
	int	i;
	int	sq;
	int	*sq_nbr;

	i = 0;
	sq = 0;
	while (arg->content[i] != '\0')
	{
		if (arg->content[i] == '\'')
			sq++;
		i++;
	}
	if (sq != 0 && sq % 2 != 0)
		return (NULL);
	sq_nbr = calloc(sizeof(int), sq + 1);
	if (!sq_nbr)
		return (NULL);
	sq_nbr[0] = sq;
	return (sq_nbr);
}

void	ft_set_final_sq_index(t_arg *arg, int *sq_nbr, t_env *env)
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
			sq_nbr[j] = sq_nbr[j] + i - ret;
			j++;
		}
		if (arg->content[i] == '$' && arg->content[i + 1]
			&& ft_set_dq_jump(&arg->content[i + 1]) > 0)
		{
			if (ft_check_var(&arg->content[i], env) > 0)
				sq_nbr[j] += ft_expand_size(&arg->content[i + 1], env) - 1;
			else
				ret += ft_set_dq_jump(&arg->content[i + 1]) + 1;
		}
		i++;
	}
}

int	ft_set_sq_jump(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	return (i);
}
