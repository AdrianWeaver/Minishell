/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:17:54 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/09 11:19:36 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*ret;
	size_t	s_len;
	size_t	i;

	i = 0;
	s_len = ft_strlen(s);
	ret = malloc(sizeof(*ret) * (n + 1));
	if (ret == 0)
		return (0);
	while (i < s_len && i < n)
	{
		ret[i] = s[i];
		i++;
	}
	while (i < n)
	{
		ret[i] = 0;
		i++;
	}
	ret[i] = 0;
	return (ret);
}
