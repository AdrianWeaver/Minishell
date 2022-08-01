/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:00:46 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/29 15:13:49 by aweaver          ###   ########.fr       */
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
	if (str[i] == '?')
		return (ft_strlen_int(ft_itoa(g_ret_value)));
	i += ft_is_valid_env_variable(str);
	str_name = ft_magic_malloc(ADD, 0, ft_substr(str, 0, i));
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
	if (*str == '?')
		return (ft_magic_malloc(ADD, 0, ft_strdup(ft_itoa(g_ret_value))));
	while (ft_isalnum(str[len]) == 1 || str[len] == '_')
		len++;
	name = ft_magic_malloc(ADD, 0, ft_substr(str, 0, len));
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

int	ft_check_and_expand(t_arg *arg, t_env *env)
{
	int		*dq;
	char	*flags;
	char	**pieces;

	if (arg->token != TOKEN_CMD)
		return (0);
	dq = ft_count_quotes(arg);
	if (!dq)
		return (-1);
	flags = ft_get_var_pos(arg->content, env);
	ft_flag_char(arg->content, flags);
	if (dq[0] != 0)
		ft_set_final_q_index(arg, flags, dq, env);
	pieces = ft_lock_expand(ft_count_expand(arg, flags, env));
	if (!pieces)
		return (-1);
	ft_final_string(arg, pieces, flags, env);
	if (flags)
		flags = ft_magic_malloc(FREE, 0, flags);
	ft_remove_quotes(arg, dq);
	dq = ft_magic_malloc(FREE, 0, dq);
	return (0);
}
