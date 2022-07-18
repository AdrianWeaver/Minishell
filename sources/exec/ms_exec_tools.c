/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitch <mitch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 08:34:23 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/15 18:58:59 by mitch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*ft_get_next_pipe(t_arg *arg)
{
	while (arg)
	{
		if (arg->token == TOKEN_PIPE)
			return (arg->next);
		arg = arg->next;
	}
	return (arg);
}

void	ft_final_path(char **paths)
{
	int		i;
	char	*slash;
	char	*temp;

	i = 0;
	slash = "/";
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], slash);
		free(paths[i]);
		paths[i] = ft_strdup(temp);
		free(temp);
		i++;
	}
}

char	**ft_get_path(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			paths = ft_split(&env[i][5], ':');
		i++;
	}
	if (paths)
		ft_final_path(paths);
	return (paths);
}

char	*ft_get_cmd(char *arg, char **paths)
{
	char	*cmd;
	int		i;

	i = 0;
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], arg);
		ft_magic_malloc(ADD, 0, cmd);
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		{
			return (cmd);
		}
		cmd = ft_magic_malloc(FREE, 0, cmd);
		i++;
	}
	return (NULL);
}

int	ft_exec(char **args, char **paths, char **env)
{
	char	*commande;

	if (execve(args[0], args, env) == -1 && env != NULL)
	{
		commande = ft_get_cmd(args[0], paths);
		execve(commande, args, env);
		if (execve(commande, args, env) == -1)
			commande = ft_magic_malloc(FREE, 0, commande);
	}
	return (0);
}

// void	ft_freetab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 		i++;
// 	while (i > 0)
// 	{
// 		free(tab[i - 1]);
// 		i--;
// 	}
// 	free(tab);
// }
