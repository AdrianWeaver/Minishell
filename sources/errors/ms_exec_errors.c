/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:36:44 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/20 09:40:29 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *file)
{
	dup2(2, STDOUT_FILENO);
	ft_printf("%s: %s\n", strerror(errno), file);
	return (-1);
}
