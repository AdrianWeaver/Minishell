/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:30:34 by aweaver           #+#    #+#             */
/*   Updated: 2022/01/26 14:12:27 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

static void	u_make_magic(t_list_printf *list, unsigned int nbr)
{
	while ((list->flag_precision == 1 && list->precision_width == 0
			&& list->flag_zero == 0 && list->flag_hyphen == 0
			&& nbr == 0) && (list->width > 0))
	{
		list->ret += ft_putchar(' ');
		list->width--;
	}
}

static void	u_nohyphen_flag(char *str, t_list_printf *list)
{
	int	str_len;

	if (list->flag_hyphen == 0 && list->flag_zero == 0 && list->width > 1)
	{
		str_len = ft_strlen_int(str);
		while (list->width > str_len)
		{
			list->ret += ft_putchar(' ');
			list->width--;
		}
	}
	if (list->flag_hyphen == 0 && list->flag_zero == 1 && list->width > 1)
	{
		str_len = ft_strlen_int(str);
		while (list->width > str_len)
		{
			list->ret += ft_putchar('0');
			list->width--;
		}
	}
}

static char	*u_flag_precision(char *tmp, t_list_printf *list,
		unsigned int unbr)
{
	char	*str;
	int		str_len;

	str_len = ft_strlen_int(tmp);
	if (list->precision_width < 0)
		list->flag_precision = 0;
	if (list->flag_precision == 1 && list->precision_width == 0 && unbr == 0)
	{
		free(tmp);
		tmp = malloc(sizeof(*tmp) * 1);
		*tmp = 0;
		return (tmp);
	}
	if (list->flag_precision == 1)
	{
		while (list->precision_width > str_len)
		{
			str = ft_strjoin("0", tmp);
			list->precision_width--;
			free(tmp);
			tmp = str;
		}
	}
	return (tmp);
}

void	ft_printf_u(unsigned int unbr, t_list_printf *list)
{
	char	*str;

	str = ft_utoa(unbr);
	str = u_flag_precision(str, list, unbr);
	u_nohyphen_flag(str, list);
	u_make_magic(list, unbr);
	list->ret += ft_putstr(str);
	list->width -= ft_strlen_int(str);
	ft_flag_hyphen(list);
	list->i++;
	free(str);
}
