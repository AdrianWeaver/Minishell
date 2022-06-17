/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:34:57 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/18 17:34:56 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t size)
{
	void	*dest_ptr;

	dest_ptr = malloc(size);
	if (dest_ptr == NULL || size == 0)
		return (NULL);
	if (old_size > size)
		old_size = size;
	if (ptr != NULL && old_size != 0)
	{
		ft_memcpy(dest_ptr, ptr, old_size);
		free(ptr);
	}
	return (dest_ptr);
}	
