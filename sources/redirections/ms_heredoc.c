/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:17:05 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/28 20:16:55 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_heredoc(t_arg *arg, t_env *env, int std[2], char **heredoc_name)
{
	int		flag;
	int		tmp_file;
	pid_t	heredoc_pid;

	*heredoc_name = ft_create_heredoc();
	flag = ft_check_delim(arg);
	ft_ignore_signal_heredoc();
	heredoc_pid = fork();
	if (heredoc_pid == 0)
	{
		tmp_file = open(*heredoc_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (tmp_file < 0)
			return (MS_NOFILE);
		ft_signal_catching_heredoc();
		if (ft_fill_heredoc(tmp_file, arg->content, flag, env) == MS_CTRLD)
		{
			arg->content[ft_strlen(arg->content) - 1] = '\0';
			ft_eprintf("\nheredoc reached EOF (wanted %s)\n", arg->content);
		}
		ft_close_heredoc(std, tmp_file);
		ft_magic_malloc(FLUSH, 0, NULL);
	}
	else
		return (ft_check_child_return(heredoc_pid));
	return (0);
}

static int	ft_finish_heredoc(char *line)
{
	if (line == NULL)
	{
		get_next_line(GNL_FLUSH);
		line = ft_magic_malloc(FREE, 0, line);
		return (MS_CTRLD);
	}
	get_next_line(GNL_FLUSH);
	line = ft_magic_malloc(FREE, 0, line);
	return (0);
}

int	ft_fill_heredoc(int file, char *delim, int flag, t_env *env)
{
	char	*line;
	char	*ret;

	line = NULL;
	ret = NULL;
	write(2, ">", 1);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strcmp(line, delim) != 0)
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
		if (line == NULL)
			break ;
	}
	return (ft_finish_heredoc(line));
}

int	ft_check_delim(t_arg *arg)
{
	int		*quotes;
	char	*delim;

	quotes = ft_count_quotes(arg);
	if (!quotes || quotes[0] == 0)
	{
		delim = ft_strjoin(arg->content, "\n");
		ft_magic_malloc(FREE, 0, arg->content);
		arg->content = delim;
		ft_magic_malloc(ADD, 0, arg->content);
		return (0);
	}
	ft_remove_quotes(arg, quotes);
	quotes = ft_magic_malloc(FREE, 0, quotes);
	delim = ft_strjoin(arg->content, "\n");
	ft_magic_malloc(FREE, 0, arg->content);
	arg->content = delim;
	ft_magic_malloc(ADD, 0, arg->content);
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
	ft_magic_malloc(FREE, 0, flags);
	ft_magic_malloc(FREE, 0, line);
	return (ret);
}
