/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 08:43:19 by aweaver           #+#    #+#             */
/*   Updated: 2022/01/24 17:42:38 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"
#include <stdarg.h>

void	ft_printf_c(int c, t_list_printf *list)
{
	if (list->flag_hyphen == 0 && list->width > 1)
	{
		while (list->width > 1)
		{
			list->ret += ft_putchar(' ');
			list->width--;
		}
	}
	list->ret += ft_putchar(c);
	list->width--;
	ft_flag_hyphen(list);
	list->i++;
}
