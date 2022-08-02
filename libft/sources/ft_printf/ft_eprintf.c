/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 10:02:21 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/02 13:31:16 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"
#include <stdarg.h>

int	ft_eprintf_conversion(const char *str, t_list_printf *list, va_list params,
		char **output)
{
	if (str[list->i] == 'c')
		ft_eprintf_c(va_arg(params, int), list, output);
	else if (str[list->i] == 's')
		ft_eprintf_s(va_arg(params, char *), list, output);
	else if (str[list->i] == 'i' || str[list->i] == 'd')
		ft_eprintf_id(va_arg(params, int), list, output);
	else if (str[list->i] == 'u')
		ft_eprintf_u(va_arg(params, unsigned int), list, output);
	else if (str[list->i] == 'p')
		ft_eprintf_p(va_arg(params, unsigned long int), list, output);
	else if (str[list->i] == 'x')
		ft_eprintf_x(va_arg(params, unsigned int), list, str, output);
	else if (str[list->i] == 'X')
		ft_eprintf_x(va_arg(params, unsigned int), list, str, output);
	else if (str[list->i] == 'o')
		ft_eprintf_o(va_arg(params, unsigned int), list, str, output);
	return (list->ret);
}

static void	ft_percent_flag(t_list_printf *list, char **output)
{
	while (list->flag_zero == 0 && list->flag_hyphen == 0
		&& list->width > 1)
	{
		list->ret++;
		*output = ft_strjoin_free(*output, " ");
		list->width--;
	}
	while (list->flag_zero == 1 && list->width > 1)
	{
		*output = ft_strjoin_free(*output, "0");
		list->ret++;
		list->width--;
	}
}

void	ft_echeck_percent(const char *str, t_list_printf *list, va_list params,
		char **output)
{
	if (str[list->i] == '%')
	{
		list->i++;
		ft_printf_parse(str, list, params);
		if ((str[list->i] == '%'))
		{
			ft_percent_flag(list, output);
			*output = ft_strjoin_free(*output, "%");
			list->ret++;
			list->width--;
			ft_eflag_hyphen(list, output);
			list->i++;
		}
		else
			ft_eprintf_conversion(str, list, params, output);
	}
}

int	ft_eprintf(const char *str, ...)
{
	va_list			params;
	t_list_printf	list;
	char			*output;

	va_start(params, str);
	list.i = 0;
	list.ret = 0;
	output = malloc(sizeof(*output) * 1);
	output[0] = '\0';
	while (str[list.i])
	{
		if (str[list.i] != '%')
		{
			output = ft_strcharjoin_free(output, (int)str[list.i]);
			list.ret++;
			list.i++;
		}
		ft_echeck_percent(str, &list, params, &output);
	}
	va_end(params);
	write(2, output, ft_strlen(output));
	free(output);
	return (list.ret);
}
