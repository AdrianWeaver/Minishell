/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cat_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:13:22 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/16 18:13:35 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_final_string(t_arg *arg, char **pieces, t_env *env)
{
	int		i;
	int		j;
	int		st;

	i = 0;
	j = -1;
	st = i;
	while (arg->content[i] != '\0')
	{
		while (arg->content[i] != '\0' && arg->content[i] != '$')
			i++;
		if (arg->content[i] == '\0' && i > st)
			pieces[++j] = ft_substr(arg->content, st, i - st);
		else if (arg->content[i] != '\0')
		{
			if (i > st)
				pieces[++j] = ft_substr(arg->content, st, (i) - st);
			if (ft_check_var(&arg->content[i], env) > 0)
				pieces[++j] = ft_get_expanded(&arg->content[i + 1], env);
			else
				i++;
			i += ft_check_var(&arg->content[i], env) + 1;
			st = i;
		}
	}
}

void	ft_final_string(t_arg *arg, char **pieces, t_env *env)
{
	char	*final;
	int		i;

	i = 0;
	ft_get_final_string(arg, pieces, env);
	final = ft_strdup(pieces[0]);
	while (pieces[++i] != NULL)
		final = ft_strjoin(final, pieces[i]);
	arg->content = ft_strdup(final);
}
