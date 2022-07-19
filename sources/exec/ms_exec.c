/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitch <mitch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 08:30:54 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/19 18:19:59 by mitch            ###   ########.fr       */
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
		return (-1);
	return (i);
}

int	ft_check_pipes(t_arg *arg, t_env *env)
{
	int	pipes;

	close(10);
	pipes = ft_count_pipes(arg);
	if (pipes == -1)
	{
		if (ft_builtin_parser(&env, arg) == 42)
			ft_try(arg, env, pipes);
	}
	else
		ft_try(arg, env, pipes);
	return (pipes);
}

int	ft_try(t_arg *arg, t_env *env, int pipes)
{
	char	**env_tab;
	char	**args_tab;
	int		std[2];
	int	i = 0;

	std[0] = dup(0);
	std[1] = dup(1);
	
	env_tab = ft_env_to_char(env);
	while (arg)
	{
		args_tab = ft_list_to_char(arg);
		if (i < pipes)
		{
			args_tab = ft_list_to_char(arg);
			ft_piped_child(arg, args_tab, env_tab, std);
			args_tab = ft_magic_malloc(FREE, 0, args_tab);
			i++;
		}
		else
			ft_child(arg, args_tab, env_tab, std);
		args_tab = ft_magic_malloc(FREE, 0, args_tab);
		arg = ft_get_next_pipe(arg);
	}
	env_tab = ft_magic_malloc(FREE, 0, env_tab);
	while (pipes >= 0)
	{
		waitpid(0, NULL, 0);
		pipes--;
	}
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	close(std[0]);
	close(std[1]);
	return (0);
}

int	ft_piped_child(t_arg *arg, char **args_tab, char **env_tab, int std[2])
{
	char	**paths;
	pid_t	child;
	int		fds[2];

	if (pipe(fds) == -1)
		return (1);
	child = fork();
	if (child == -1)
		return (1);
	if (child == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		paths = ft_get_path(env_tab);
		ft_executor(arg, args_tab, paths, env_tab);
		ft_close_child(fds, std);
		ft_magic_malloc(FLUSH, 0, NULL);
	}
	else
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[1]);
		close(fds[0]);
	}
	return (0);
}

int	ft_child(t_arg *arg, char **args_tab, char **env_tab, int std[2])
{
	char	**paths;
	pid_t	child;
	int		fds[2];

	if (pipe(fds) == -1)
		return (1);
	child = fork();
	if (child == -1)
		return (1);
	if (child == 0)
	{
		paths = ft_get_path(env_tab);
		ft_executor(arg, args_tab, paths, env_tab);
		ft_close_child(fds, std);
		ft_magic_malloc(FLUSH, 0, NULL);
	}
	close(fds[1]);
	close(fds[0]);
	dup2(std[1], STDOUT_FILENO);
	waitpid(0, NULL, 0);
	return (0);
}

int	ft_executor(t_arg *arg, char **args_tab, char **paths, char **env_tab)
{
	char	*cmd;
	t_env	*env;

	(void)paths;
	env = ft_env_to_list(env_tab);
	if (ft_builtin_parser(&env, arg) == 42)
	{
		// if (ft_check_cmd(args_tab[0]) != 0)
		// 	return (-1);
		if (execve(args_tab[0], args_tab, env_tab) == -1 && env_tab)
		{
			cmd = ft_get_cmd(args_tab[0], paths);
			if (cmd == NULL)
			{
				ft_eprintf("%s: %s\n", args_tab[0], NOT_FOUND);
				return (1);
			}
			if (execve(cmd, args_tab, env_tab) == -1)
			{
				ft_eprintf("%s: %s\n", args_tab[0], NOT_FOUND);
				cmd = ft_magic_malloc(FREE, 0, cmd);
				return (-1);
			}
		}
	}
	return (1);
}

void	ft_close_child(int fds[2], int std[2])
{
	close(fds[1]);
	close(fds[0]);
	close(std[1]);
	close(std[0]);
}
