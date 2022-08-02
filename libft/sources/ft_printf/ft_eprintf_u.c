/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eprintf_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:30:34 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/02 13:13:18 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

static void	u_make_magic(t_list_printf *list, unsigned int nbr, char **output)
{
	while ((list->flag_precision == 1 && list->precision_width == 0
			&& list->flag_zero == 0 && list->flag_hyphen == 0
			&& nbr == 0) && (list->width > 0))
	{
		*output = ft_strjoin_free(*output, " ");
		list->width--;
	}
}

static void	u_nohyphen_flag(char *str, t_list_printf *list, char **output)
{
	int	str_len;

	if (list->flag_hyphen == 0 && list->flag_zero == 0 && list->width > 1)
	{
		str_len = ft_strlen_int(str);
		while (list->width > str_len)
		{
			*output = ft_strjoin_free(*output, " ");
			list->width--;
		}
	}
	if (list->flag_hyphen == 0 && list->flag_zero == 1 && list->width > 1)
	{
		str_len = ft_strlen_int(str);
		while (list->width > str_len)
		{
			*output = ft_strjoin_free(*output, "0");
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

void	ft_eprintf_u(unsigned int unbr, t_list_printf *list, char **output)
{
	char	*str;

	str = ft_utoa(unbr);
	str = u_flag_precision(str, list, unbr);
	u_nohyphen_flag(str, list, output);
	u_make_magic(list, unbr, output);
	*output = ft_strjoin_free(*output, str);
	list->width -= ft_strlen_int(str);
	ft_eflag_hyphen(list, output);
	list->i++;
	free(str);
}
