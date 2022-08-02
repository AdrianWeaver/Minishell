/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eprintf_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 08:43:19 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/02 13:12:14 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"
#include <stdarg.h>

void	ft_eprintf_c(int c, t_list_printf *list, char **output)
{
	if (list->flag_hyphen == 0 && list->width > 1)
	{
		while (list->width > 1)
		{
			*output = ft_strjoin_free(*output, " ");
			list->ret++;
			list->width--;
		}
	}
	*output = ft_strcharjoin_free(*output, c);
	list->ret++;
	list->width--;
	ft_eflag_hyphen(list, output);
	list->i++;
}
