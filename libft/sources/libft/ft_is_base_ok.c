/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_base_ok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:23:44 by aweaver           #+#    #+#             */
/*   Updated: 2022/01/19 11:58:08 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_base_ok(int base_len, char *base_format)
{
	int	i;
	int	j;

	i = 0;
	if ((int)ft_strlen(base_format) >= base_len && base_len > 1)
	{
		while (base_format[i])
		{
			if (base_format[i] == '+' || base_format[i] == '-')
				return (0);
			if (ft_isprint(base_format[i]) == 0)
				return (0);
			j = i + 1;
			while (base_format[j])
			{
				if (base_format[i] == base_format[j])
					return (0);
				j++;
			}
			i++;
		}
		return (1);
	}
	return (0);
}
