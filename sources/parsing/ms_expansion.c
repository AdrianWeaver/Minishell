/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:00:46 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/17 17:55:20 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_env_var(char *str, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strcmp(str, temp->name) == 0)
			return (0);
		temp = temp->next;
	}
	return (-1);
}

int	ft_check_var(char *str, t_env *env)
{
	char	*sub;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str[i] == '$' && str[i + 1])
	{
		i++;
		j = i;
		while (str[i] && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
			i++;
		sub = ft_substr(str, j, i - j);
		if (!sub)
			return (-1);
		if (ft_check_env_var(sub, env) == 0)
			return (i - j);
	}
	return (-1);
}

char	**ft_count_expand(t_arg *arg, t_env *env)
{
	char	**pieces;
	int		exp;
	int		i;
	int		st;

	exp = 0;
	i = 0;
	while (arg->content[i] != '\0')
	{
		st = i;
		while (arg->content[i] && arg->content[i] != '$')
			i++;
		if (i > st)
			exp++;
		if (arg->content[i] && ft_check_var(&arg->content[i], env) > 0)
		{
			exp++;
			i += ft_check_var(&arg->content[i], env) + 1;
		}
		else if (arg->content[i] != '\0')
			i++;
	}
	if (exp > 0)
		pieces = malloc(sizeof(char *) * exp + 1);
	if (pieces)
		pieces[exp] = NULL;
	return (pieces);
}

int	ft_expand_size(char *str, t_env *env)
{
	t_env	*temp;
	char	*str_name;
	int		i;
	int		len;

	temp = env;
	i = 0;
	len = 0;
	while (str[i] && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	str_name = ft_substr(str, 0, i);
	if (!str_name)
		return (-1);
	while (temp != NULL)
	{
		if (ft_strcmp(str_name, temp->name) == 0)
			break ;
		temp = temp->next;
	}
	len = ft_strlen(temp->content[0]) - ft_strlen(temp->name);
	if (temp == NULL)
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
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, name) == 0)
		{
			var_ret = ft_strdup(temp->content[0]);
			break ;
		}
		temp = temp->next;
	}
	return (var_ret);
}
