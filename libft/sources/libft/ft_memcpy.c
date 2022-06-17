/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:09:38 by aweaver           #+#    #+#             */
/*   Updated: 2021/12/01 12:27:45 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest_c;
	char	*src_c;

	if (dest == 0 && src == 0 && n > 0)
		return (0);
	dest_c = (char *)dest;
	src_c = (char *)src;
	while (n--)
		*dest_c++ = *src_c++;
	return (dest);
}
