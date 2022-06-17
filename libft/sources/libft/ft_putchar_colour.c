/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:16:24 by aweaver           #+#    #+#             */
/*   Updated: 2022/01/21 14:34:06 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putchar_colour(char c, char *colour)
{
	ft_putstr(colour);
	write(1, &c, 1);
	ft_putstr(NOCOLOUR);
	return (1);
}
