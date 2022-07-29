/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 08:30:54 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/28 14:27:21 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_pipes(t_arg *arg)
{
	int	i;

	i = 0;
	while (arg)
	{
		if (arg->token == TOKEN_PIPE)
			i++;
		arg = arg->next;
	}
	if (i == 0)
		return (0);
	return (i);
}

int	ft_try(t_arg *arg, t_env *env, int pipes, int std[2])
{
	int		i;
	int		child_return;

	i = -1;
	while (arg)
	{
		if (++i < pipes)
			ft_piped_child(arg, env, std);
		else
			ft_child(arg, env, std);
		arg = ft_get_next_pipe(arg);
	}
	dup2(std[1], STDOUT_FILENO);
	dup2(std[0], STDIN_FILENO);
	while (pipes >= 0)
	{
		child_return = ft_check_child_return(-1);
		if (child_return)
			return (child_return);
		pipes--;
	}
	return (0);
}

int	ft_piped_child(t_arg *arg, t_env *env, int std[2])
{
	pid_t	child;
	int		fds[2];
	int		*currents;

	if (pipe(fds) == -1)
		return (1);
	child = fork();
	if (child == -1)
		return (1);
	if (child == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		currents = ft_redirection(arg);
		ft_executor(arg, env, std, currents);
		ft_close_child(fds, std, currents);
		ft_magic_malloc(FLUSH, 0, NULL);
	}
	else
	{
		ft_ignore_signal();
		dup2(fds[0], STDIN_FILENO);
		close(fds[1]);
		close(fds[0]);
	}
	return (0);
}

int	ft_child(t_arg *arg, t_env *env, int std[2])
{
	pid_t	child;
	int		fds[2];
	int		*currents;

	if (pipe(fds) == -1)
		return (1);
	child = fork();
	if (child == -1)
		return (1);
	if (child == 0)
	{
		dup2(std[1], STDOUT_FILENO);
		currents = ft_redirection(arg);
		ft_executor(arg, env, std, currents);
		ft_close_child(fds, std, currents);
		ft_magic_malloc(FLUSH, 0, NULL);
	}
	else
	{
		ft_ignore_signal();
		close(fds[1]);
		close(fds[0]);
	}
	return (0);
}

int	ft_executor(t_arg *arg, t_env *env, int std[2], int *currents)
{
	char	*cmd;
	char	**env_tab;
	char	**args_tab;
	char	**paths;

	args_tab = ft_list_to_char(arg);
	env_tab = ft_env_to_char(env);
	paths = ft_get_path(env_tab);
	if ((currents[0] >= 0 && currents[1] >= 0)
		&& ft_builtin_parser(&env, arg, std) == 42)
	{
		if (args_tab && ft_check_cmd(args_tab[0]) == 0)
		{
			if (execve(args_tab[0], args_tab, env_tab) == -1 && env_tab)
			{
				cmd = ft_get_cmd(args_tab[0], paths);
				if (cmd == NULL || execve(cmd, args_tab, env_tab) == -1)
					ft_eprintf("%s: %s\n", args_tab[0], NOT_FOUND);
				cmd = ft_magic_malloc(FREE, 0, cmd);
			}
		}
		args_tab = ft_magic_malloc(FREE, 0, args_tab);
		env = ft_magic_malloc(FREE, 0, env);
	}
	return (-1);
}
