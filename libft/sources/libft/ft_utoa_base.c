/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:40:47 by aweaver           #+#    #+#             */
/*   Updated: 2022/01/26 08:30:30 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "libft.h"

static int	ft_count_udigits_base(unsigned int nb, unsigned int base_len)
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

static int	ft_is_ubase_ok(unsigned int base_len, char *base_format)
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

static char	*ft_get_ptr(int digits, unsigned int base_len, char *base_format)
{
	char	*ret;

	if (ft_is_ubase_ok(base_len, base_format) == 0)
		return (NULL);
	ret = malloc(sizeof(*ret) * (digits + 1));
	if (ret != 0)
		ret[digits] = 0;
	return (ret);
}

char	*ft_utoa_base(unsigned int n, unsigned int base_len, char *base_format)
{
	int		nsave;
	int		digits;
	char	*ret;

	nsave = n;
	digits = ft_count_udigits_base(n, base_len);
	ret = ft_get_ptr(digits, base_len, base_format);
	if (ret == 0)
		return (0);
	if ((n > 9 && n <= base_len) || nsave == 0)
		ret[0] = '0';
	while (n > 0)
	{
		ret[digits - 1] = base_format[(n % base_len)];
		digits--;
		n /= base_len;
	}
	return (ret);
}	
