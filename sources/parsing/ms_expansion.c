/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:00:46 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/12 18:04:37 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_var(char *str)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	if (str[i] == '$' && (ft_isalnum(str[i + 1]) == 1 || str[i + 1] == '_'))
	{
		i++;
		while (str[i] && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		{
			i++;
			j++;
		}
		return (j);
	}
	return (0);
}

char	**ft_count_expand(t_arg *arg)
{
	char	**pieces;
	int		exp;
	int		i;
	int		st;

	exp = 0;
	i = 0;
	st = i;
	while (arg->content[i] != '\0')
	{
		while (arg->content[i] != '\0' &&ft_check_var(&arg->content[i]) < 1)
			i++;
		if (i > st)
			exp++;
		if (arg->content[i] == '$' && (ft_isalnum(arg->content[i + 1]) == 1
				|| arg->content[i + 1] == '_'))
			exp++;
		i += ft_check_var(&arg->content[i]) + 1;
	}
	if (exp > 0)
	{
		pieces = malloc(sizeof(char *) * exp + 1);
		if (!pieces)
			return (NULL);
		pieces[exp] = NULL;
	}
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
		{
			len = ft_strlen(temp->content[0]) - ft_strlen(temp->name);
			break ;
		}
		temp = temp->next;
	}
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

void	ft_get_final_string(t_arg *arg, char **pieces, t_env *env)
{
	char	*env_content;
	int		i;
	int		j;
	int		st;

	i = 0;
	j = 0;
	st = i;
	while (arg->content[i] != '\0')
	{
		while (arg->content[i + 1] != '\0' && ft_check_var(&arg->content[i]) < 1)
			i++;
		if (arg->content[i] != '\0')
		{
			if (ft_check_var(&arg->content[i]) > 0)
				env_content = ft_get_expanded(&arg->content[i + 1], env);
			if (i > st)
			{
				pieces[j] = ft_substr(arg->content, st, i - st);
				j++;
			}
			if (env_content != NULL)
			{
				pieces[j] = ft_strdup(env_content);
				free(env_content);
				j++;
			}
			i+= ft_check_var(&arg->content[i]) + 1;
			st = i;
		}
	}
	for (int x = 0; pieces[x] != NULL;x++)
	{
		printf("pieces[%d] = %s\n", x, pieces[x]);
	}
}