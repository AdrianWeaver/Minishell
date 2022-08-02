/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 08:27:19 by jcervoni          #+#    #+#             */
/*   Updated: 2022/08/02 15:06:01 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_builtin_parser(t_env **env, t_arg *arg, int std[2])
{
	int	ret;

	ret = 1;
	while (arg && arg->token != TOKEN_PIPE && arg->token != TOKEN_CMD)
		arg = arg->next;
	if (arg && ft_strcmp(arg->content, "echo") == 0)
		ret = ft_echo(arg->next);
	else if (arg && ft_strcmp(arg->content, "env") == 0)
		ret = ft_print_env(*env, ft_list_to_char(arg->next));
	else if (arg && ft_strcmp(arg->content, "pwd") == 0)
		ret = ft_print_pwd(std);
	else if (arg && ft_strcmp(arg->content, "cd") == 0)
		ret = ft_cd(*env, ft_list_to_char(arg->next), std);
	else if (arg && ft_strcmp(arg->content, "export") == 0)
		ret = ft_export(env, ft_list_to_char(arg->next));
	else if (arg && ft_strcmp(arg->content, "unset") == 0)
		ret = ft_unset(env, ft_list_to_char(arg->next));
	else if (arg && ft_strcmp(arg->content, "exit") == 0)
		ft_exit_manager(arg->next, std);
	return (ret);
}
