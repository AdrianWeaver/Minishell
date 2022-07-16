/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitch <mitch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 08:30:54 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/16 18:50:34 by mitch            ###   ########.fr       */
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

int	ft_try(t_arg *arg, t_env *env)
{
	char	**env_tab;
	char	**args_tab;
	int		pipes;
	int		std[2];

	std[0] = dup(0);
	std[1] = dup(1);
	
	env_tab = ft_env_to_char(env);
	pipes = ft_count_pipes(arg);
	while (arg)
	{
		args_tab = ft_list_to_char(arg);
		if (pipes > 0)
		{
			args_tab = ft_list_to_char(arg);
			ft_piped_child(arg, args_tab, env_tab);
			args_tab = ft_magic_malloc(FREE, 0, args_tab);
			pipes--;
		}
		else
			ft_child(arg, args_tab, env_tab, std);
		args_tab = ft_magic_malloc(FREE, 0, args_tab);
		arg = ft_get_next_pipe(arg);
	}
	env_tab = ft_magic_malloc(FREE, 0, env_tab);
	waitpid(0, NULL, 0);
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	close(std[0]);
	close(std[1]);
	return (0);
}


int	ft_piped_child(t_arg *arg, char **args_tab, char **env_tab)
{
	char	**paths;
	pid_t	child;
	int		fds[2];

	(void)arg;
	if (pipe(fds) == -1)
		return (1);
	child = fork();
	if (child == -1)
		return (1);
	if (child == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		// ft_set_redirections(arg);
		paths = ft_get_path(env_tab);
		if (ft_executor(args_tab, paths, env_tab) == -1)
		{
			close(fds[1]);
			close(fds[0]);
			ft_magic_malloc(FLUSH, 0, NULL);
		}
	}
	else
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[1]);
		close(fds[0]);
		// waitpid(0, NULL, 0);
	}
	return (0);
}

int	ft_child(t_arg *arg, char **args_tab, char **env_tab, int std[2])
{
	char	**paths;
	pid_t	child;
	
	(void)arg;
	child = fork();
	if (child == -1)
		return (1);
	if (child == 0)
	{
		// ft_set_redirections(arg);
		paths = ft_get_path(env_tab);
		if (ft_executor(args_tab, paths, env_tab) == -1)
		{
			close(1);
			close(0);
			ft_magic_malloc(FLUSH, 0, NULL);
		}
	}
	else
	{
		waitpid(0, NULL, 0);
		dup2(std[1], STDOUT_FILENO);
	}
	return (0);
}

int	ft_executor(char **args_tab, char **paths, char **env_tab)
{
	char	*cmd;

	if (execve(args_tab[0], args_tab, env_tab) == -1 && env_tab)
	{
		cmd = ft_get_cmd(args_tab[0], paths);
		if (cmd == NULL)
			return (1);
		if (execve(cmd, args_tab, env_tab) == -1)
			cmd = ft_magic_malloc(FREE, 0, cmd);
	}
	return (-1);
}
