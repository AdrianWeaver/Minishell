/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:07:03 by aweaver           #+#    #+#             */
/*   Updated: 2022/01/18 09:08:45 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putendl(char *s)
{
	int	ret;

	if (!s)
		return (0);
	ret = 0;
	ret += ft_putstr(s);
	ret += ft_putchar('\n');
	return (ret);
}
