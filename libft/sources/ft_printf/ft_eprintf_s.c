/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eprintf_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:59:49 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/02 13:13:18 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

static void	s_noflag_width(char *str, t_list_printf *list, char **output)
{
	int	str_len;

	if (list->flag_hyphen == 0 && list->width > 0)
	{
		if (list->flag_precision == 1)
		{
			if (ft_strlen_int(str) < list->precision_width)
				str_len = ft_strlen(str);
			else
				str_len = list->precision_width;
		}
		else
			str_len = ft_strlen_int(str);
		while ((*str == 0 && list->width > 0) || (list->width > str_len))
		{
			*output = ft_strjoin_free(*output, " ");
			list->ret++;
			list->width--;
		}
	}
}

static void	s_flag_precision(char *str, t_list_printf *list, char **output)
{
	if (list->precision_width < 0)
		list->flag_precision = 0;
	if (list->flag_precision == 1)
	{
		while (*str && list->precision_width > 0)
		{
			*output = ft_strcharjoin_free(*output, *str);
			list->precision_width--;
			str++;
			list->width--;
		}
	}
	else if (list->flag_precision == 0)
	{
		while (*str)
		{
			*output = ft_strcharjoin_free(*output, *str);
			str++;
			list->width--;
		}
	}
}

static void	s_nullstring(char *str, t_list_printf *list, int i, char **output)
{
	while ((list->width > 6 && list->flag_hyphen == 0) || (list->width > 0
			&& list->flag_hyphen == 0 && list->flag_precision == 1
			&& (list->width > list->precision_width || list->width > 6)))
	{
		*output = ft_strjoin_free(*output, " ");
		list->width--;
	}
	if (list->flag_precision == 1)
	{
		while (list->precision_width > 0 && str[i])
		{
			*output = ft_strcharjoin_free(*output, str[i]);
			i++;
			list->precision_width--;
			list->width--;
		}
	}
	else if (list->flag_precision == 0)
	{
		*output = ft_strjoin_free(*output, str);
		list->width -= 6;
	}
	ft_eflag_hyphen(list, output);
	free(str);
}

void	ft_eprintf_s(char *str, t_list_printf *list, char **output)
{
	char	*null_str;
	int		count;

	count = 0;
	if (!str)
	{
		null_str = ft_strdup("(null)");
		s_nullstring(null_str, list, count, output);
		list->i++;
	}
	else
	{
		s_noflag_width(str, list, output);
		s_flag_precision(str, list, output);
		ft_eflag_hyphen(list, output);
		list->i++;
	}
}
