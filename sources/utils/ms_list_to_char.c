/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list_to_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 10:37:54 by aweaver           #+#    #+#             */
/*   Updated: 2022/06/23 11:42:55 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_get_cmd_nb(t_arg *list)
{
	int	size;

	size = 0;
	while (list)
	{
		if (list->token == TOKEN_PIPE)
			break ;
		if (list->token == TOKEN_CMD)
			size++;
		list = list->next;
	}
	return (size);
}

char	**ft_list_to_char(t_arg *list)
{
	char	**ret;
	int		i;
	int		size;

	i = 0;
	size = ft_get_cmd_nb(list);
	ret = malloc(sizeof(*ret) * size + 1);
	while (list)
	{
		if (list->token == TOKEN_PIPE)
			break ;
		if (list->token == TOKEN_CMD)
		{
			ret[i] = list->token;
			i++;
		}
		list = list->next;
	}
	return (ret);
}
