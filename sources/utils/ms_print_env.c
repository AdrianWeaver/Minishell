/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:29:57 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/12 14:37:17 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_print_env(t_env *env_list)
{
	int		i;

	while (env_list)
	{
		i = 0;
		ft_printf("%s=", env_list->name);
		while (env_list->content[i])
		{
			ft_printf("%s", env_list->content[i]);
			i++;
			if (env_list->content[i])
				ft_printf(":");
		}
		env_list = env_list->next;
		ft_printf("\n");
	}
}
