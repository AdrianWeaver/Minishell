/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:20:39 by aweaver           #+#    #+#             */
/*   Updated: 2021/11/25 13:37:13 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_c;
	const unsigned char	*src_c;

	dest_c = dest;
	src_c = src;
	if (dest > src)
	{
		while (n--)
			dest_c[n] = src_c[n];
	}
	else
		return (ft_memcpy(dest, src, n));
	return (dest);
}
