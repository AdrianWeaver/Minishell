/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:00:09 by aweaver           #+#    #+#             */
/*   Updated: 2022/01/25 17:16:27 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

static void	p_noflag_width(char *str, t_list_printf *list)
{
	int	str_len;

	if (list->flag_hyphen == 0 && list->width > 1)
	{
		if (list->flag_precision == 1)
		{
			if ((int)ft_strlen(str) < list->precision_width)
				str_len = ft_strlen(str);
			else
				str_len = list->precision_width;
		}
		else
			str_len = ft_strlen(str);
		while (list->width > str_len)
		{
			list->ret += ft_putchar(' ');
			list->width--;
		}
	}
}

static char	*p_addr_prefix(char *prefix, char *tmp)
{
	char	*str;

	str = ft_strjoin(prefix, tmp);
	free(tmp);
	return (str);
}

void	ft_printf_p(unsigned long int addr, t_list_printf *list)
{
	char	*str;

	if (addr == 0)
	{
		str = PTR_NULL;
	}
	else
	{
		str = ft_ultoa_base((size_t)addr, 16, "0123456789abcdef");
		str = p_addr_prefix("0x", str);
	}
	p_noflag_width(str, list);
	list->ret += ft_putstr(str);
	list->width -= ft_strlen(str);
	ft_flag_hyphen(list);
	list->i++;
	if (addr != 0)
		free(str);
}
