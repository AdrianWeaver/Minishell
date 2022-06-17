/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:39:08 by aweaver           #+#    #+#             */
/*   Updated: 2022/02/16 22:28:00 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str_joined;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	str_joined = malloc(sizeof(*str_joined) * (ft_strlen(s1) + ft_strlen(s2)
				+ 1));
	if (str_joined == 0)
		return (0);
	str_joined[0] = 0;
	ft_strcat(str_joined, s1);
	free(s1);
	ft_strcat(str_joined, s2);
	return (str_joined);
}
