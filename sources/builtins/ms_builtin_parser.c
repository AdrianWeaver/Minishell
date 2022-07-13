/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 08:27:19 by jcervoni          #+#    #+#             */
/*   Updated: 2022/06/15 11:45:20 by jcervoni         ###   ########.fr       */
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

void	ft_builtin_parser(t_env **env, t_arg *arg)
{
	if (arg && ft_strcmp(arg->content, "echo") == 0)
		ft_echo(arg->next);
	if (arg && ft_strcmp(arg->content, "env") == 0)
		ft_print_env(*env);
	if (arg && ft_strcmp(arg->content, "pwd") == 0)
		ft_print_pwd();
	if (arg && ft_strcmp(arg->content, "cd") == 0)
		ft_cd(*env, arg->next->content);
	if (arg && ft_strcmp(arg->content, "export") == 0)
		ft_export(env, ft_list_to_char(arg->next));
	if (arg && ft_strcmp(arg->content, "unset") == 0)
		ft_unset(env, ft_list_to_char(arg->next));
	if (arg && ft_strcmp(arg->content, "exit") == 0)
		write(2, "wesh t'as pas codé exit encore\n", 33);
}
