/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mitch_main_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitch <mitch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:18:40 by aweaver           #+#    #+#             */
/*   Updated: 2022/07/15 20:46:24 by mitch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_test(t_arg *arg, t_env *env)
{
	int		*dq;
	char	*flags;
	char	**pieces;

	dq = ft_count_quotes(arg);
	if (!dq)
		return (-1);
	flags = ft_get_var_pos(arg->content, env);
	ft_flag_char(arg->content, flags);
	if (dq[0] != 0)
		ft_set_final_q_index(arg, flags, dq, env);
	pieces = ft_lock_expand(ft_count_expand(arg, flags, env));
	if (!pieces)
		return (-1);
	ft_final_string(arg, pieces, flags, env);
	if (flags)
		flags = ft_magic_malloc(FREE, 0, flags);
	ft_remove_quotes(arg, dq);
	dq = ft_magic_malloc(FREE, 0, dq);
	return (0);
}

void	ft_get_redirections(t_arg *arg)
{
	t_arg	*head;

	head = arg;
	while (arg)
	{
		arg = ft_get_infile(arg, head);
		arg = ft_get_heredoc(arg, head);
		arg = ft_get_outfile(arg, head);
		arg = ft_get_appendout(arg, head);
		ft_check_double_pipe(arg, head);
		arg = arg->next;
	}
}

int	main(int ac, char *av[], char *env[])
{
	t_arg	*verif;
	t_arg	*temp;
	t_env	*env_list;
	char	*line;

	(void)ac;
	(void)av;
	verif = NULL;
	env_list = ft_env_to_list(env);
	while (1)
	{
		line = ft_display_prompt();
		if (line == NULL)
			break ;
		verif = ft_get_args(line);
		line = ft_magic_malloc(FREE, 0, line);
		if (verif != NULL)
		{
			ft_set_token(verif);
			temp = verif;
			ft_get_redirections(verif);
			while (verif != NULL)
			{
				// ft_redirection(verif);
				if (verif->token == TOKEN_HEREDOC && verif->content[0] != '<')
					ft_heredoc(verif, env_list);
				if (ft_test(verif, env_list) == -1)
				{
					if (ft_test(verif, env_list) == -1)
					{
						printf("Missing or extra dquote\n");
						ft_clear_arg(temp);
						ft_free_env(env_list);
						line = ft_magic_malloc(FREE, 0, line);
						exit(1);
					}
				}
				
				verif = verif->next;
			}
			verif = temp;
			while (verif)
			{
				ft_builtin_parser(&env_list, verif);
				verif = verif->next;
			}
		}
	}
	rl_clear_history();
	ft_magic_malloc(FLUSH, 0, NULL);
	return (0);
}
