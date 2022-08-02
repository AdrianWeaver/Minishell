/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:18:40 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/02 18:03:08 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ret_value;

t_arg	*ft_init_shell(int std[2])
{
	char	*line;
	t_arg	*arg;

	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	line = NULL;
	arg = NULL;
	line = ft_display_prompt(std);
	if (line == NULL)
	{
		close(std[0]);
		close(std[1]);
		ft_exit_manager(arg, std);
	}
	arg = ft_get_args(line);
	line = ft_magic_malloc(FREE, 0, line);
	return (arg);
}

int	ft_launch_and_test_heredocs(t_arg *head, t_env **env, int std[2])
{
	int		heredoc_return;
	char	*heredoc_name;

	heredoc_name = NULL;
	heredoc_return = ft_redir_heredoc(head, *env, std, &heredoc_name);
	if (heredoc_return != 0)
	{
		if (heredoc_return == MS_NOFILE)
			return (-1);
		else
		{
			g_ret_value = heredoc_return;
			unlink(heredoc_name);
		}
		return (-1);
	}
	return (0);
}

int	ft_main_loop(t_arg *arg, t_env **env, int std[2])
{
	t_arg	*head;

	head = arg;
	ft_set_token(arg);
	if (ft_get_redirections(arg) == 0)
	{
		while (arg != NULL)
		{
			if (ft_check_and_expand(arg, env) == -1)
			{
				printf("Missing or extra dquote\n");
				ft_clear_arg(head);
				return (1);
			}
			if (arg)
				arg = arg->next;
		}
		if (ft_launch_and_test_heredocs(head, env, std) == -1)
			return (-1);
		ft_check_pipes(head, env, std);
		dup2(std[0], STDIN_FILENO);
		dup2(std[1], STDOUT_FILENO);
	}
	ft_clear_arg(head);
	return (0);
}

int	main(int ac, char *av[], char *env[])
{
	t_arg	*arg;
	t_env	*env_list;
	int		std[2];

	(void)ac;
	(void)av;
	g_ret_value = 0;
	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	arg = NULL;
	env_list = NULL;
	env_list = ft_env_to_list(env, std);
	while (1)
	{
		ft_signal_catching();
		arg = ft_init_shell(std);
		if (arg == NULL)
			continue ;
		ft_main_loop(arg, &env_list, std);
	}
	close(std[0]);
	close(std[1]);
	rl_clear_history();
	ft_magic_malloc(FLUSH, 0, NULL);
	return (0);
}
