/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_colour.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:36:34 by aweaver           #+#    #+#             */
/*   Updated: 2022/01/21 14:57:31 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putstr_colour(char *str, char *colour)
{
	int	str_len;

	str_len = ft_strlen_int(str);
	ft_putstr(colour);
	write(1, str, str_len);
	ft_putstr(NOCOLOUR);
	return (str_len);
}
