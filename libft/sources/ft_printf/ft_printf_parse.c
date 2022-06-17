/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 11:25:07 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/08 10:28:49 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

static void	ft_printf_parseloop(const char *str, t_list_printf *list)
{
	while (str[list->i] == '0' || str[list->i] == '-' || str[list->i] == '+'
		|| str[list->i] == ' ' || str[list->i] == '#')
	{
		if (str[list->i] == '0')
			list->flag_zero = 1;
		if (str[list->i] == '-')
			list->flag_hyphen = 1;
		if (str[list->i] == '+')
			list->flag_plus = 1;
		if (str[list->i] == ' ')
			list->flag_space = 1;
		if (str[list->i] == '#')
			list->flag_hashtag = 1;
		list->i++;
	}
}

static void	ft_printf_check_star(const char *str, t_list_printf *list,
		va_list params)
{
	if (str[list->i] == '*' && list->flag_precision == 0)
	{
		list->width = va_arg(params, int);
		list->i++;
	}
	else if (str[list->i] == '*' && list->flag_precision == 1)
	{
		list->precision_width = va_arg(params, int);
		list->i++;
	}
}

void	ft_printf_parse(const char *str, t_list_printf *list, va_list params)
{
	ft_lstreset(list);
	while (str[list->i] && ft_strchr(CONVERSION, str[list->i]) == 0)
	{
		ft_printf_parseloop(str, list);
		ft_printf_check_star(str, list, params);
		if (ft_isdigit(str[list->i]) == 1 && list->flag_precision == 0)
		{
			list->width = ft_atoi(&str[list->i]);
			while (ft_isdigit(str[list->i]) == 1)
			{
				list->i++;
			}
		}
		if (str[list->i] == '.')
		{
			list->flag_precision = 1;
			list->i++;
			list->precision_width = ft_atoi(&str[list->i]);
			while (ft_isdigit(str[list->i]) == 1)
				list->i++;
		}	
	}
	ft_printf_check_flags(list);
}
