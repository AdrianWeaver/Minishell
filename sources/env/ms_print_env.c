/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@42.fr>                     +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:29:57 by aweaver           #+#    #+#             */
/*   Updated: 2022/07/14 17:53:01 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_print_env(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->content)
		{
			ft_printf("%s=", env_list->name);
			ft_printf("%s\n", env_list->content);
		}
		env_list = env_list->next;
	}
}
