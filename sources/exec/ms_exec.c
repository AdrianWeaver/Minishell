/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 08:30:54 by jcervoni          #+#    #+#             */
/*   Updated: 2022/08/02 18:08:01 by aweaver          ###   ########.fr       */
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

int	ft_try(t_arg *arg, t_env **env, int pipes, int std[2])
{
	int		i;
	int		child_return;
	int		last_child_pid;
	int		*child_pids;

	i = -1;
	child_pids = ft_magic_malloc(MALLOC, (sizeof(int) * pipes), NULL);
	while (arg)
	{
		if (++i < pipes)
			child_pids[i] = ft_piped_child(arg, env, std);
		else
			last_child_pid = ft_child(arg, env, std);
		arg = ft_get_next_pipe(arg);
	}
	dup2(std[1], STDOUT_FILENO);
	dup2(std[0], STDIN_FILENO);
	i = -1;
	child_return = ft_check_child_return(last_child_pid);
	while (++i < pipes)
		ft_check_child_return(child_pids[i]);
	if (child_return == SIGQUIT)
		ft_eprintf("Quit (core dumped)\n");
	g_ret_value = child_return;
	return (child_return);
}

int	ft_piped_child(t_arg *arg, t_env **env, int std[2])
{
	pid_t	child;
	int		fds[2];
	int		*currents;
	int		ret;

	if (pipe(fds) == -1)
		return (1);
	child = fork();
	if (child == -1)
		return (1);
	if (child == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		currents = ft_redirection(arg);
		ft_close_child(fds, std, currents);
		ret = ft_executor(arg, env, std, currents);
		ft_magic_malloc(FLUSH, ret, NULL);
	}
	ft_ignore_signal();
	dup2(fds[0], STDIN_FILENO);
	close(fds[1]);
	close(fds[0]);
	return (child);
}

int	ft_child(t_arg *arg, t_env **env, int std[2])
{
	pid_t	child;
	int		fds[2];
	int		*currents;
	int		ret;

	if (pipe(fds) == -1)
		return (1);
	child = fork();
	if (child == -1)
		return (1);
	if (child == 0)
	{
		dup2(std[1], STDOUT_FILENO);
		currents = ft_redirection(arg);
		ft_close_child(fds, std, currents);
		ret = ft_executor(arg, env, std, currents);
		ft_magic_malloc(FLUSH, ret, NULL);
	}
	else
	{
		ft_ignore_signal();
		close(fds[1]);
		close(fds[0]);
	}
	return (child);
}

int	ft_executor(t_arg *arg, t_env **env, int std[2], int *currents)
{
	char	*cmd;
	char	**env_tab;
	char	**args_tab;
	char	**paths;

	env_tab = ft_env_to_char(*env);
	paths = ft_get_path(env_tab);
	if ((currents[0] >= 0 && currents[1] >= 0)
		&& ft_is_a_builtin(arg) == 0)
	{
		args_tab = ft_list_to_char_exec(arg);
		if (args_tab && ft_check_cmd(args_tab[0]) == 0)
		{
			ft_ignore_signal();
			if (execve(args_tab[0], args_tab, env_tab) == -1)
			{
				cmd = ft_get_cmd(args_tab[0], paths);
				if (cmd == NULL || execve(cmd, args_tab, env_tab) == -1)
					return (ft_eprintf("%s:%s\n", args_tab[0], NOT_FOUND), 127);
				cmd = ft_magic_malloc(FREE, 0, cmd);
			}
		}
	}
	return (ft_builtin_parser(env, arg, std));
}
