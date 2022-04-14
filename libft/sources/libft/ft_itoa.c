/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:40:47 by aweaver           #+#    #+#             */
/*   Updated: 2021/11/30 10:23:32 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_count_digit(long int n)
{
	int	digits;

	digits = 1;
	if (n < 0)
	{
		digits++;
		n = -n;
	}
	while (n / 10 > 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	long int	nbr;
	int			digits;
	char		*ret;

	nbr = (long)n;
	digits = ft_count_digit(n);
	ret = malloc(sizeof(*ret) * (digits + 1));
	if (!ret)
		return (0);
	ret[digits] = 0;
	if (nbr < 0)
	{
		ret[0] = '-';
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		ret[digits - 1] = (nbr % 10) + '0';
		digits--;
		nbr /= 10;
	}
	if (n == 0)
		ret[0] = '0';
	return (ret);
}
