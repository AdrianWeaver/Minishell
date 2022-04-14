/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:10:35 by aweaver           #+#    #+#             */
/*   Updated: 2022/01/18 09:16:14 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	int	ret;
	int	hold;

	ret = 0;
	hold = 0;
	if (n == -2147483648)
	{
		hold++;
		n++;
	}
	if (n < 0)
	{
		ret += ft_putchar('-');
		n = -n;
	}
	if (n / 10 > 0)
	{
		ret += ft_putnbr(n / 10);
	}
	ret += ft_putchar((n % 10) + hold + '0');
	return (ret);
}
