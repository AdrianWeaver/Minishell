/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:30:57 by aweaver           #+#    #+#             */
/*   Updated: 2022/01/26 08:30:44 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "libft.h"

static int	ft_count_uldigits_base(size_t nb, size_t base_len)
{
	int	digits;

	digits = 1;
	if (base_len < 1)
		return (-1);
	while (nb / base_len > 0)
	{
		nb = nb / base_len;
		digits++;
	}
	return (digits);
}

static int	ft_is_ulbase_ok(size_t base_len, char *base_format)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(base_format) >= base_len && base_len > 1)
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

static char	*ft_get_ptr(int digits, size_t base_len, char *base_format)
{
	char	*ret;

	if (ft_is_ulbase_ok(base_len, base_format) == 0)
		return (NULL);
	ret = malloc(sizeof(*ret) * (digits + 1));
	if (ret != 0)
		ret[digits] = 0;
	return (ret);
}

char	*ft_ultoa_base(size_t n, size_t base_len, char *base_format)
{
	size_t				nbr;
	int					digits;
	char				*ret;

	nbr = n;
	digits = ft_count_uldigits_base(n, base_len);
	ret = ft_get_ptr(digits, base_len, base_format);
	if (ret == 0)
		return (0);
	if ((nbr > 9 && nbr <= base_len) || n == 0)
		ret[0] = '0';
	while (nbr > 0)
	{
		ret[digits - 1] = base_format[(nbr % base_len)];
		digits--;
		nbr /= base_len;
	}
	return (ret);
}	
