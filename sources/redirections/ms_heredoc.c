/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:17:05 by jcervoni          #+#    #+#             */
/*   Updated: 2022/06/23 16:17:08 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_heredoc(t_arg *arg, t_env *env)
{
	int		tmp_file;
	int		flag;
	pid_t	doc;

	flag = ft_check_delim(arg);
	tmp_file = open(".tmp_doc", O_CREAT | O_WRONLY, 0644);
	unlink(".tmp_doc");
	if (tmp_file < 0)
		return (-1);
	doc = fork();
	if (doc == 0)
	{
		dup2(tmp_file, STDOUT_FILENO);
		ft_fill_heredoc(tmp_file, arg->content, flag, env);
		ft_clear_arg(arg);
		ft_magic_malloc(FLUSH, 0, NULL);
		close(tmp_file);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(0, NULL, 0);
		close(tmp_file);
	}
	return (0);
}

void	ft_fill_heredoc(int file, char *delim, int flag, t_env *env)
{
	char	*line;
	char	*stop;
	char	*ret;

	line = NULL;
	ret = NULL;
	stop = ft_strjoin(delim, "\n");
	dup2(file, STDOUT_FILENO);
	line = get_next_line(0);
	while (strcmp(line, stop) != 0)
	{
		ft_magic_malloc(ADD, 0, line);
		if (flag == 0)
		{
			ret = ft_expand_heredoc(line, env);
			printf("%s", ret);
		}
		else
			printf("%s\n", line);
		ft_magic_malloc(FREE, 0, ret);
		line = get_next_line(0);
	}
	get_next_line(GNL_FLUSH);
	line = ft_magic_malloc(FREE, 0, line);
	stop = ft_magic_malloc(FREE, 0, stop);
}

int	ft_check_delim(t_arg *arg)
{
	int	*quotes;

	quotes = ft_count_quotes(arg);
	if (!quotes || quotes[0] == 0)
		return (0);
	ft_remove_quotes(arg, quotes);
	quotes = ft_magic_malloc(FREE, 0, quotes);
	return (1);
}

char	*ft_expand_heredoc(char *line, t_env *env)
{
	char	*flags;
	char	**pieces;
	char	*ret;

	ret = NULL;
	flags = ft_get_var_pos(line, env);
	fprintf(stderr, "flags == %s\n", flags);
	pieces = ft_lock_expand(ft_count_hd_expand(line, flags, env));
	if (!pieces)
		return (NULL);
	ret = ft_final_hd_string(line, pieces, flags, env);
	if (flags)
		ft_magic_malloc(FREE, 0, flags);
	ft_magic_malloc(FREE, 0, line);
	return (ret);
}
