/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:00:46 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/19 12:01:08 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_expand(t_arg *arg, char *flags, t_env *env)
{
	int		exp;
	int		i;
	int		st;

	exp = 0;
	i = -1;
	while (arg->content[++i] != '\0')
	{
		st = i;
		while (arg->content[i] && flags[i] != '2')
			i++;
		if (i > st)
			exp++;
		if (arg->content[i] && flags[i] == '2'
			&& ft_check_var(&arg->content[i], env) > 0)
			exp++;
	}
	return (exp);
}

char	**ft_lock_expand(int size)
{
	char	**pieces;

		pieces = malloc(sizeof(char *) * (size + 1));
	if (!pieces)
		return (NULL);
	if (size == 0)
		pieces[1] = NULL;
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
	len = ft_strlen(env->content[0]) - ft_strlen(env->name);
	if (env == NULL)
		return (ft_strlen(str_name));
	free(str_name);
	return (len);
}

char	*ft_get_expanded(char *str, t_env *env)
{
	t_env	*temp;
	char	*var_ret;
	char	*name;
	int		len;

	len = 0;
	temp = env;
	var_ret = NULL;
	while (ft_isalnum(str[len]) == 1 || str[len] == '_')
		len++;
	name = ft_substr(str, 0, len);
	if (!name)
		return (NULL);
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, name) == 0)
		{
			var_ret = ft_strdup(temp->content[0]);
			break ;
		}
		temp = temp->next;
	}
	free(name);
	return (var_ret);
}
