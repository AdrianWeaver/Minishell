/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:17:05 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/27 12:31:57 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_heredoc(t_arg *arg, t_env *env, int std[2], char *name)
{
	int		tmp_file;
	int		flag;
	pid_t	doc;

	flag = ft_check_delim(arg);
	tmp_file = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp_file < 0)
		return (-1);
	ft_ignore_signal();
	doc = fork();
	if (doc == 0)
	{
		ft_signal_catching_heredoc();
		ft_fill_heredoc(tmp_file, arg->content, flag, env);
		close(std[0]);
		close(std[1]);
		close(tmp_file);
		ft_magic_malloc(FLUSH, 0, NULL);
	}
	else
	{
		waitpid(0, NULL, 0);
		close(tmp_file);
	}
	return (0);
}

void	ft_finish_heredoc(char *line, char *stop)
{
	get_next_line(GNL_FLUSH);
	line = ft_magic_malloc(FREE, 0, line);
	stop = ft_magic_malloc(FREE, 0, stop);
}

void	ft_fill_heredoc(int file, char *delim, int flag, t_env *env)
{
	char	*line;
	char	*stop;
	char	*ret;

	line = NULL;
	ret = NULL;
	stop = ft_strjoin(delim, "\n");
	write(2, ">", 1);
	line = get_next_line(STDIN_FILENO);
	while (strcmp(line, stop) != 0)
	{
		ft_magic_malloc(ADD, 0, line);
		if (flag == 0)
		{
			ret = ft_expand_heredoc(line, env);
			ft_putstr_fd(ret, file);
		}
		else
			ft_putstr_fd(line, file);
		ft_magic_malloc(FREE, 0, ret);
		write(2, ">", 1);
		line = get_next_line(STDIN_FILENO);
	}
	ft_finish_heredoc(line, stop);
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
	pieces = ft_lock_expand(ft_count_hd_expand(line, flags, env));
	if (!pieces)
		return (NULL);
	ret = ft_final_hd_string(line, pieces, flags, env);
	if (flags)
		ft_magic_malloc(FREE, 0, flags);
	ft_magic_malloc(FREE, 0, line);
	return (ret);
}
