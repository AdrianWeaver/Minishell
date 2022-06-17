/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 11:23:38 by aweaver           #+#    #+#             */
/*   Updated: 2022/01/16 11:23:39 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* the purpose of this function is to count the length of a number
 * then return it */

int	ft_count_digits(long int nb)
{
	int	digits;

	digits = 1;
	if (nb < 0)
	{
		digits++;
		nb = -nb;
	}
	while (nb / 10 > 0)
	{
		nb = nb / 10;
		digits++;
	}
	return (digits);
}
