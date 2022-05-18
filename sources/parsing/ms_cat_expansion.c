/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cat_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:13:22 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/18 10:48:07 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_final_string(t_arg *arg, char **pieces, char *flags, t_env *env)
{
	char	*final;
	int		i;

	i = 0;
	final = NULL;
	ft_get_strings(arg, pieces, flags, env);
	final = ft_strdup(pieces[0]);
	while (pieces[++i])
	{
		final = ft_strjoin_free(final, pieces[i]);
		free(pieces[i]);
	}
	if (pieces)
	{
		free(pieces[0]);
		free(pieces);
	}
	arg->content = ft_strdup(final);
	free(final);
}

char	*ft_get_var_pos(char *str, t_env *env)
{
	int	i;
	char	*flags;

	i = 0;
	flags = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!flags)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && ft_check_var(&str[i], env) > 0)
			flags[i] = '2';
		else if (str[i] == '$' && str[i + 1] && ft_set_dq_jump(&str[i + 1]) > 0)
			flags[i] = '1';
		else
			flags[i] = '0';
		i++;
	}
	flags[i] = '\0';
	return (flags);
}

void	ft_get_strings(t_arg *arg, char **pieces, char *flags, t_env *env)
{
	int	i;
	int	j;
	int	st;

	i = 0;
	j = -1;
	while (arg->content[i])
	{
		if (flags[i] && flags[i] == '0')
		{
			st = i;
			while (flags[i] && flags[i] == '0')
				i++;
			pieces[++j] = ft_substr(arg->content, st, i - st);
		}
		if (flags[i] && flags[i] == '1')
			i += ft_set_dq_jump(&arg->content[i + 1]) + 1;
		if (flags[i] && flags[i] == '2')
		{
			pieces[++j] = ft_get_expanded(&arg->content[i + 1], env);
			i += ft_check_var(&arg->content[i], env) + 1;
		}
		if (flags[i] == '\0' && j == -1)
			pieces[++j] = "";
	}
}
