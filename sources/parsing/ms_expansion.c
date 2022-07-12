/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:00:46 by jcervoni          #+#    #+#             */
/*   Updated: 2022/06/23 14:19:36 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_expand(t_arg *arg, char *flags, t_env *env)
{
	int	exp;
	int	i;
	int	st;

	exp = 0;
	i = 0;
	if (!arg)
		return (0);
	while (arg->content[i] != '\0')
	{
		st = i;
		while (flags[i] && flags[i] != '2' && flags[i] != '1')
			i++;
		if (i > st)
			exp++;
		if (flags[i] && flags[i] == '2'
			&& ft_check_var(&arg->content[i], env) > 0)
		{
			exp++;
			i += ft_set_q_jump(&arg->content[i + 1]) + 1;
		}
		else if (flags[i] && flags[i] == '1')
			i += ft_set_q_jump(&arg->content[i + 1]) + 1;
	}
	return (exp);
}

char	**ft_lock_expand(int size)
{
	char	**pieces;

	pieces = ft_magic_malloc(MALLOC, sizeof(char *) * (size + 1), NULL);
	if (!pieces)
		return (NULL);
	else
		pieces[size] = NULL;
	return (pieces);
}

int	ft_expand_size(char *str, t_env *env)
{
	char	*str_name;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i] && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	str_name = ft_substr(str, 0, i);
	if (!str_name)
		return (-1);
	while (env != NULL)
	{
		if (ft_strcmp(str_name, env->name) == 0)
			break ;
		env = env->next;
	}
	if (len < 0)
		return (0);
	len = ft_strlen(env->content) - ft_strlen(env->name);
	if (env == NULL)
		return (ft_strlen(str_name));
	str_name = ft_magic_malloc(FREE, 0, str_name);
	return (len);
}

char	*ft_get_expanded(char *str, t_env *env)
{
	char	*var_ret;
	char	*name;
	int		len;

	len = 0;
	var_ret = NULL;
	while (ft_isalnum(str[len]) == 1 || str[len] == '_')
		len++;
	name = ft_substr(str, 0, len);
	ft_magic_malloc(ADD, 0, name);
	if (!name)
		return (NULL);
	while (env != NULL)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			var_ret = ft_strdup(env->content);
			ft_magic_malloc(ADD, 0, var_ret);
			break ;
		}
		env = env->next;
	}
	name = ft_magic_malloc(FREE, 0, name);
	return (var_ret);
}
