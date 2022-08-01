/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:35:51 by jcervoni          #+#    #+#             */
/*   Updated: 2022/08/01 12:21:23 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_prompt(int std[2])
{
	char	*name;
	char	*cwd;
	char	*path;

	name = NULL;
	cwd = ft_get_pwd(std);
	path = ft_get_short_path(cwd);
	if (!cwd)
		return (NULL);
	name = ft_strdup("🦆Rubberduckers🦆");
	name = ft_strjoin_free(name, ":");
	name = ft_strjoin_free(name, path);
	name = ft_strjoin_free(name, "$ ");
	path = ft_magic_malloc(FREE, 0, path);
	cwd = ft_magic_malloc(FREE, 0, cwd);
	return (name);
}

int	ft_check_for_home(char *cwd)
{
	int	i;

	i = 0;
	if (cwd == NULL)
	{
		rl_clear_history();
		ft_eprintf(MS_NOCWD);
		ft_magic_malloc(FLUSH, 1, NULL);
	}
	while (cwd[i] && ft_strncmp(&cwd[i], "home", 4) != 0)
		i++;
	if (cwd[i] == '\0')
		return (0);
	i += 4;
	if (cwd[i] == 's')
		i++;
	if (cwd[i] == '/')
		i++;
	else
		return (0);
	while (cwd[i] && cwd[i] != '/')
		i++;
	if (cwd[i] == '/')
		i++;
	return (i);
}

char	*ft_get_short_path(char *cwd)
{
	int		i;
	char	*tmp_short_cwd;
	char	*short_cwd;

	i = ft_check_for_home(cwd);
	short_cwd = NULL;
	if (i == 0)
		return (ft_strdup(cwd));
	if (i > 0)
	{
		tmp_short_cwd = ft_strdup(&cwd[i]);
		short_cwd = ft_magic_malloc(ADD, 0, ft_strjoin("~", tmp_short_cwd));
		free(tmp_short_cwd);
		tmp_short_cwd = NULL;
	}
	return (short_cwd);
}

//char	*ft_get_short_path(char *cwd)
//{
	//char	*path;
	//char	*tmp;
	//int		i;
	//int		j;
//
	//path = NULL;
	//tmp = NULL;
	//i = 6;
	//j = 0;
	//ft_eprintf("CWD = %s\n", cwd);
	//while (ft_strncmp(&cwd[j], "homes", 5) != 0)
		//j++;
	//path = ft_strdup(&cwd[j + i]);
	//ft_magic_malloc(ADD, 0, path);
	//if (path)
	//{
		//while (path[i] != '/')
			//i++;
		//tmp = ft_strdup(&path[i + 1]);
		//ft_magic_malloc(ADD, 0, tmp);
		//path = ft_magic_malloc(FREE, 0, path);
		//path = ft_strjoin("~/", tmp);
		//tmp = ft_magic_malloc(FREE, 0, NULL);
		//return (path);
	//}
	//return (cwd);
//}

char	*ft_display_prompt(int std[2])
{
	char	*line;
	char	*prompt;

	if (ft_is_interactive() == 0)
		line = get_next_line(STDIN_FILENO);
	else
	{
		prompt = ft_get_prompt(std);
		line = readline(prompt);
		add_history(line);
		ft_magic_malloc(ADD, 0, prompt);
		prompt = ft_magic_malloc(FREE, 0, prompt);
	}
	if (line == NULL)
	{
		line = ft_magic_malloc(FREE, 0, line);
		return (NULL);
	}
	return (line);
}
