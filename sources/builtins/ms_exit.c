/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:18:08 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/02 14:18:26 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exit(unsigned char exit_code, int std[2])
{
	g_ret_value = exit_code;
	close(std[0]);
	close(std[1]);
	rl_clear_history();
	ft_magic_malloc(FLUSH, g_ret_value, NULL);
}

void	ft_write_exit(void)
{
	if (ft_is_interactive() == 1)
		write(2, "exit\n", 5);
}

void	ft_exit_manager(t_arg *arg, int std[2])
{
	int		i;
	char	*exit_phrase;

	i = 0;
	if (arg == NULL || arg->content == NULL)
	{
		ft_write_exit();
		ft_exit(0, std);
	}
	exit_phrase = arg->content;
	if (exit_phrase[0] == '+' || exit_phrase[0] == '-')
		i++;
	while (exit_phrase[i])
	{
		if (ft_isdigit(exit_phrase[i]) == 0)
		{
			ft_write_exit();
			ft_eprintf("minishell: exit: %s: numeric argument required\n",
				exit_phrase);
			ft_exit(2, std);
		}
		i++;
	}
	ft_write_exit();
	ft_exit(ft_atoi(exit_phrase), std);
}
