/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:12:49 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/08 12:04:23 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

static char	*id_flag_plus_space(char *str, t_list_printf *list, int nbr)
{
	char	*tmp;

	if (list->flag_plus == 1 && nbr >= 0)
	{
		tmp = ft_strjoin("+", str);
		free(str);
		str = tmp;
	}
	if (list->flag_space == 1 && !(nbr < 0))
	{
		(void)tmp;
		list->ret += ft_putchar(' ');
		list->width--;
	}
	return (str);
}

static char	*id_nohyphen_flag(char *str, t_list_printf *list, int nbr)
{
	char	*tmp;

	if (list->flag_hyphen == 0 && list->flag_zero == 0 && list->width > 1)
	{
		while (list->width > ft_strlen_int(str))
		{
			list->ret += ft_putchar(' ');
			list->width--;
		}
	}
	if (list->flag_hyphen == 0 && list->flag_zero == 1 && list->width > 1)
	{
		while (list->width > ft_strlen_int(str))
		{
			if (nbr < 0)
				tmp = ft_strjoin("-0", &str[1]);
			else if (list->flag_plus == 0)
				tmp = ft_strjoin("0", str);
			else if (list->flag_plus == 1)
				tmp = ft_strjoin("+0", &str[1]);
			free(str);
			str = tmp;
		}
	}
	return (str);
}

static char	*id_make_magic(char *str, t_list_printf *list, int nbr)
{
	char	*tmp;
	int		str_len;

	str_len = ft_strlen_int(str);
	if (nbr < 0 || (list->flag_plus == 1 && nbr >= 0))
		str_len--;
	if (list->flag_precision == 1)
	{
		while (list->precision_width > str_len)
		{
			if (nbr < 0)
				tmp = ft_strjoin("-0", &str[1]);
			else if (nbr >= 0 && list->flag_plus == 1)
				tmp = ft_strjoin("+0", &str[1]);
			else
				tmp = ft_strjoin("0", str);
			str_len++;
			free(str);
			str = tmp;
		}
	}
	return (str);
}

static char	*id_flag_precision(char *str, t_list_printf *list, int nbr)
{
	if (list->precision_width < 0)
		list->flag_precision = 0;
	if (list->flag_precision == 1 && list->precision_width == 0 && nbr == 0
		&& list->flag_plus == 0)
	{
		free(str);
		str = malloc(sizeof(*str) * 1);
		*str = 0;
		return (str);
	}
	else if (list->flag_precision == 1 && list->precision_width == 0
		&& nbr == 0 && list->flag_plus == 1)
	{
		free(str);
		str = ft_strdup("+");
		return (str);
	}
	str = id_make_magic(str, list, nbr);
	return (str);
}

void	ft_printf_id(int nbr, t_list_printf *list)
{
	char	*str;

	str = ft_itoa(nbr);
	str = id_flag_plus_space(str, list, nbr);
	str = id_flag_precision(str, list, nbr);
	str = id_nohyphen_flag(str, list, nbr);
	while ((list->flag_precision == 1 && list->precision_width == 0
			&& list->flag_zero == 0 && list->flag_hyphen == 0
			&& nbr == 0) && (list->width > 0) && list->flag_plus == 0)
	{
		list->ret += ft_putchar(' ');
		list->width--;
	}
	list->ret += ft_putstr(str);
	list->width -= ft_strlen_int(str);
	ft_flag_hyphen(list);
	list->i++;
	free(str);
}
