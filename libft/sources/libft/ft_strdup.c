/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:19:36 by aweaver           #+#    #+#             */
/*   Updated: 2021/11/26 13:56:04 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	s_len;
	size_t	i;

	i = 0;
	s_len = ft_strlen(s);
	ret = malloc(sizeof(*ret) * (s_len + 1));
	if (ret == 0)
		return (0);
	while (i < s_len)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}
