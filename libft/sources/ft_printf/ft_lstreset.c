/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 10:56:07 by aweaver           #+#    #+#             */
/*   Updated: 2022/01/14 10:56:20 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_lstreset(t_list_printf *list)
{
	list->flag_zero = 0;
	list->flag_hyphen = 0;
	list->flag_precision = 0;
	list->precision_width = 0;
	list->flag_hashtag = 0;
	list->flag_space = 0;
	list->flag_plus = 0;
	list->width = 0;
}
