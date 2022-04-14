/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:06:02 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/28 14:01:55 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_skip_zeros(char *str, int len, int i)
{
	while (str[i] == '0' && str[i + 1] != '\0')
	{
		ft_memcpy(&str[i], &str[i + 1], ft_strlen(&str[i + 1]));
		str[len - 1] = 0;
		len--;
	}
	return (str);
}

int	ft_is_int(char *str)
{
	int	i;
	int	len;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	len = ft_strlen(str);
	str = ft_skip_zeros(str, len, i);
	len = ft_strlen(str);
	while (str[i])
		if (ft_isdigit(str[i++]) == 0)
			return (0);
	if (len < 10)
		return (1);
	if (len > 11)
		return (0);
	if (len == 10)
		if (ft_strcmp("2147483647", str) < 0)
			return (0);
	if (len == 11)
		if ((ft_strcmp("-2147483648", str) < 0)
			|| (str[0] == '+' && ft_strcmp("+2147483647", str) < 0))
			return (0);
	return (1);
}
