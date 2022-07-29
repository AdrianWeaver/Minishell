/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 08:27:19 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/29 10:00:50 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//SUBJECT CHEAT SHEET
//echo option -n
//cd relative or absolute path
//pwd no option
//export no option
//unset no option
//env no option and no args
//exit no options

void	ft_exit(unsigned char exit_code, int std[2])
{
	g_ret_value = exit_code;
	close(std[0]);
	close(std[1]);
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

int	ft_builtin_parser(t_env **env, t_arg *arg, int std[2])
{
	while (arg && arg->token != TOKEN_PIPE && arg->token != TOKEN_CMD)
		arg = arg->next;
	if (arg && ft_strcmp(arg->content, "echo") == 0)
		return (ft_echo(arg->next));
	else if (arg && ft_strcmp(arg->content, "env") == 0)
		return (ft_print_env(*env, ft_list_to_char(arg->next)));
	else if (arg && ft_strcmp(arg->content, "pwd") == 0)
		return (ft_print_pwd());
	else if (arg && ft_strcmp(arg->content, "cd") == 0)
		return (ft_cd(*env, ft_list_to_char(arg->next)));
	else if (arg && ft_strcmp(arg->content, "export") == 0)
		return (ft_export(env, ft_list_to_char(arg->next)));
	else if (arg && ft_strcmp(arg->content, "unset") == 0)
		return (ft_unset(env, ft_list_to_char(arg->next)));
	else if (arg && ft_strcmp(arg->content, "exit") == 0)
		ft_exit_manager(arg->next, std);
	return (42);
}
