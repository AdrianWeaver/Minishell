/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:05:52 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/20 10:25:52 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_cmd(char *cmd)
{
	int	i;

	i = -1;
	if (cmd)
		while (cmd[++i])
			if (cmd[i] != '/' && cmd[i] != '.')
				break ;
	if (cmd[i] == '\0')
	{
		ft_eprintf("minishell: %s: %s\n", cmd, IS_DIR);
		return (-1);
	}
	return (0);
}
