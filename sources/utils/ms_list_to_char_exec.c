/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list_to_char_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:02:32 by jcervoni          #+#    #+#             */
/*   Updated: 2022/08/03 11:02:34 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_check_cmd_space(char *content)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (content[j] != '\0')
	{
		if (content[j] == ' ')
		{
			i++;
			while (content[j] != '\0' && content[j] == ' ')
				j++;
		}
		else
			j++;
	}
	return (i);
}

static int	ft_get_cmd_nb_exec(t_arg *list)
{
	int	size;

	size = 0;
	while (list)
	{
		if (list->token == TOKEN_PIPE)
			break ;
		if (list->token == TOKEN_CMD)
		{
			size++;
			size += ft_check_cmd_space(list->content);
		}
		list = list->next;
	}
	return (size);
}

static int	ft_split_cmd(char **ret, char *content)
{
	char	**split_cmd;
	int		i;

	split_cmd = NULL;
	i = 0;
	split_cmd = ft_magic_malloc(ADD, 0, ft_split(content, ' '));
	if (!split_cmd)
		return (-1);
	while (i <= ft_check_cmd_space(content))
	{
		ft_magic_malloc(ADD, 0, split_cmd[i]);
		ret[i] = split_cmd[i];
		i++;
	}
	return (i);
}

char	**ft_list_to_char_exec(t_arg *list)
{
	char	**ret;
	int		i;
	int		size;

	i = 0;
	size = ft_get_cmd_nb_exec(list);
	ret = ft_magic_malloc(MALLOC, sizeof(*ret) * (size + 1), NULL);
	if (size == 0)
		return (NULL);
	ret[size] = 0;
	while (list && list->token != TOKEN_PIPE)
	{
		if (list->token == TOKEN_CMD)
		{
			if (ft_check_cmd_space(list->content) != 0)
				i += ft_split_cmd(&ret[i], list->content);
			else
			{
				ret[i] = list->content;
				i++;
			}
		}
		list = list->next;
	}
	return (ret);
}
