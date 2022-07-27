/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:35:51 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/25 17:20:33 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_prompt(void)
{
	char	*name;
	char	*cwd;
	char	*path;

	name = NULL;
	cwd = ft_get_pwd();
	path = ft_get_short_path(cwd);
	if (!cwd)
		return (NULL);
	name = ft_strdup("🦆Rubberduckers🦆");
	name = ft_strjoin_free(name, ":");
	name = ft_strjoin_free(name, path);
	name = ft_strjoin_free(name, "$ ");
<<<<<<< HEAD
	path = ft_magic_malloc(FREE, 0, path);
	cwd = ft_magic_malloc(FREE, 0, cwd);
=======
	ft_magic_malloc(FREE, 0, path);
	ft_magic_malloc(FREE, 0, cwd);
>>>>>>> 67cc5b4 (ADD MS_HEREDOC.C :)
	return (name);
}

char	*ft_get_short_path(char *cwd)
{
	char	*path;
	char	*tmp;
	int		i;
	int		j;

	path = NULL;
	tmp = NULL;
	i = 6;
	j = 0;
	while (ft_strncmp(&cwd[j], "home", 4) != 0)
		j++;
	path = ft_strdup(&cwd[j + i]);
	ft_magic_malloc(ADD, 0, path);
	if (path)
	{
		while (path[i] != '/')
			i++;
		tmp = ft_strdup(&path[i + 1]);
		ft_magic_malloc(ADD, 0, tmp);
		path = ft_magic_malloc(FREE, 0, path);
		path = ft_strjoin("~/", tmp);
		tmp = ft_magic_malloc(FREE, 0, NULL);
		return (path);
	}
	return (cwd);
}

char	*ft_display_prompt(void)
{
	char	*line;
	char	*prompt;

	prompt = ft_get_prompt();
	line = readline(prompt);
	add_history(line);
	ft_magic_malloc(ADD, 0, prompt);
	prompt = ft_magic_malloc(FREE, 0, prompt);
	if (line == NULL || ft_strcmp(line, "stop") == 0)
	{
		line = ft_magic_malloc(FREE, 0, line);
		return (NULL);
	}
	return (line);
}
