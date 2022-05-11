/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:51:25 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/10 17:42:03 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell"

int	ft_echo(char *to_print)
{
	int	i;
	int	end;

	i = 0;
	while (to_print[i] != '\0')
	{
		if (to_print[0] == '"')
		{
			end = 1;
			while (to_print[++i] != '"' && to_print[i])
			{
				end++;
			}
		}
	return (0);
}