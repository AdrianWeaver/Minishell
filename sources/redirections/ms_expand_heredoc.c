/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:17:34 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/27 12:33:29 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_hd_expand(char *line, char *flags, t_env *env)
{
	int	exp;
	int	i;
	int	st;

	exp = 0;
	i = 0;
	while (line[i])
	{
		st = i;
		while (line[i] && flags[i] != '2' && flags[i] != '1')
			i++;
		if (i > st)
			exp++;
		if (line[i] && flags[i] == '2'
			&& ft_check_var(&line[i], env) > 0)
		{
			exp++;
			i += ft_set_q_jump(&line[i + 1]) + 1;
		}
		else if (line[i] && flags[i] == '1')
			i += ft_set_q_jump(&line[i + 1]) + 1;
	}
	return (exp);
}

char	*ft_final_hd_string(char *line, char **pieces, char *flags, t_env *env)
{
	char	*final;
	int		i;

	final = NULL;
	i = 1;
	ft_get_hd_strings(line, pieces, flags, env);
	final = ft_strdup(pieces[0]);
	if (pieces[0])
		ft_magic_malloc(FREE, 0, pieces[0]);
	while (pieces && pieces[i] != NULL)
	{
		final = ft_strjoin_free(final, pieces[i]);
		ft_magic_malloc(FREE, 0, pieces[i]);
		i++;
	}
	ft_magic_malloc(ADD, 0, final);
	if (pieces)
		pieces = ft_magic_malloc(FREE, 0, pieces);
	return (final);
}

void	ft_get_hd_strings(char *line, char **pieces, char *flags, t_env *env)
{
	int	i;
	int	j;
	int	st;

	i = 0;
	j = -1;
	while (line[i])
	{
		if (flags[i] && flags[i] == '0')
		{
			st = i;
			while (flags[i] && flags[i] == '0')
				i++;
			pieces[++j] = ft_substr(line, st, i - st);
		}
		if (flags[i] && flags[i] == '1')
			i += ft_set_q_jump(&line[i + 1]) + 1;
		if (flags[i] && flags[i] == '2')
		{
			pieces[++j] = ft_get_expanded(&line[i + 1], env);
			i += ft_check_var(&line[i], env) + 1;
		}
	}
	if (flags[i] == '\0' || j == -1)
		pieces[++j] = NULL;
}
