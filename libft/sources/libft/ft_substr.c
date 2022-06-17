/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:40:41 by aweaver           #+#    #+#             */
/*   Updated: 2021/12/02 12:21:24 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static size_t	ft_strnlen(char const *s, size_t size)
{
	size_t	i;

	i = 0;
	while (s[i] && i < size)
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	s_len;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
	{
		ret = malloc(sizeof(*ret) * 1);
		*ret = 0;
		return (ret);
	}
	s_len = ft_strnlen (&s[start], len);
	ret = malloc(sizeof(*ret) * (s_len + 1));
	if (!ret)
		return (0);
	while (i < s_len)
	{
		ret[i] = (char)s[start + i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}
