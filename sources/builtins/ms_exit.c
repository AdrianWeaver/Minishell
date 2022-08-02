/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:18:08 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/02 23:04:29 by aweaver          ###   ########.fr       */
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

int	ft_check_exit_first_arg(char *exit_phrase, unsigned char *exit_code)
{
	int	i;

	i = 0;
	if (ft_strlen_int(exit_phrase) > 19)
	{
		ft_eprintf("minishell: exit: %s: numeric argument required\n",
			exit_phrase);
		*exit_code = 2;
		return (0);
	}
	if (exit_phrase[0] == '+' || exit_phrase[0] == '-')
		i++;
	while (exit_phrase[i])
	{
		if (ft_isdigit(exit_phrase[i]) == 0)
		{
			ft_eprintf("minishell: exit: %s: numeric argument required\n",
				exit_phrase);
			*exit_code = 2;
			return (0);
		}
		i++;
	}
	*exit_code = ft_atoi(exit_phrase);
	return (1);
}

static int	ft_exit_arg_number(t_arg *arg)
{
	int	i;

	i = 0;
	while (arg && arg->token != TOKEN_PIPE)
	{
		if (arg->token == TOKEN_CMD)
		{
			ft_eprintf("commande reconnue = %s\n", arg->content);
			i++;
		}
		arg = arg->next;
	}
	return (i);
}

int	ft_exit_manager(t_arg *arg, int std[2])
{
	int				arg_one_isok;
	int				arg_number;
	unsigned char	exit_code;

	exit_code = 0;
	arg_number = ft_exit_arg_number(arg);
	ft_eprintf("debug arg number %d\n", arg_number);
	if (ft_count_pipes(arg) == 0)
		ft_write_exit();
	if (arg == NULL || arg->token == TOKEN_PIPE
		|| (arg->content == NULL && arg_number == 1))
		ft_exit(g_ret_value, std);
	arg_one_isok = ft_check_exit_first_arg(arg->content, &exit_code);
	if (arg_number > 1 && arg_one_isok == 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else
		ft_exit(exit_code, std);
	return (0);
}
