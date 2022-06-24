/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_hyphen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:35:19 by aweaver           #+#    #+#             */
/*   Updated: 2022/01/24 17:45:57 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

void	ft_flag_hyphen(t_list_printf *list)
{
	while (list->flag_hyphen == 1 && list->width > 0)
	{
		list->ret += ft_putchar(' ');
		list->width--;
	}
}
