/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 08:27:19 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/25 17:44:54 by jcervoni         ###   ########.fr       */
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

int	ft_builtin_parser(t_env **env, t_arg *arg, int std[2])
{
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
	{
		write(1, "exit\n", 5);
		close(std[0]);
		close(std[1]);
		ft_magic_malloc(FLUSH, 0, NULL);
	}
	return (42);
}
