/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:17:05 by jcervoni          #+#    #+#             */
/*   Updated: 2022/07/25 13:52:18 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_heredoc(t_arg *arg, t_env *env, int std[2], char *name)
{
	int		tmp_file;
	int		flag;
	pid_t	doc;

	(void)std;
	flag = ft_check_delim(arg);
	tmp_file = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (tmp_file < 0)
			return (-1);
	doc = fork();
	if (doc == 0)
	{
		
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

void	ft_fill_heredoc(int file, char *delim, int flag, t_env *env)
{
	char	*line;
	char	*stop;
	char	*ret;

	line = NULL;
	ret = NULL;
	stop = ft_strjoin(delim, "\n");
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
		line = get_next_line(STDIN_FILENO);
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
	pieces = ft_lock_expand(ft_count_hd_expand(line, flags, env));
	if (!pieces)
		return (NULL);
	ret = ft_final_hd_string(line, pieces, flags, env);
	if (flags)
		ft_magic_malloc(FREE, 0, flags);
	ft_magic_malloc(FREE, 0, line);
	return (ret);
}

char	*ft_manage_heredoc(t_arg *arg, t_env *env, int std[2])
{
	int		i;
	char	*secret_name;
	char	*name_end;

	secret_name = NULL;
	i = 2147483647;
	while (arg && arg->token != TOKEN_PIPE)
	{
		if (arg->token == TOKEN_HEREDOC)
		{
			dup2(std[0], STDIN_FILENO);
			name_end = ft_itoa(i);
			ft_magic_malloc(ADD, 0, name_end);
			secret_name = ft_strjoin("/tmp/.MiNiShElL#@tmp", name_end);
			fprintf(stderr, "secret_name == %s\n", secret_name);
			ft_magic_malloc(ADD, 0, secret_name);
			if (arg->content[0] == '<')
				arg = arg->next;
			ft_heredoc(arg, env, std, secret_name);
		}
		i--;
		arg = arg->next;
	}
	return (secret_name);
}