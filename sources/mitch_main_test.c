/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mitch_main_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:18:40 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/18 10:39:35 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_test(t_arg *arg, t_env *env)
{
	int		*dq;
	char	*flags;
	char	**pieces;

	pieces = ft_lock_expand(ft_count_expand(arg, env));
	if (!pieces)
		return (-1);
	dq = ft_count_dquotes(arg);
	if (!dq)
		return (-1);
	ft_set_final_dq_index(arg, dq, env);
	flags = ft_get_var_pos(arg->content, env);
	ft_final_string(arg, pieces, flags, env);
	free(flags);
	ft_remove_dquotes(arg, dq);
	free(dq);
	return (0);
}

int	main(int ac, char *av[], char *env[])
{
	char	*test;
	t_arg	*verif;
	t_arg	*temp;
	t_env	*env_list;
	
	(void)env;
	(void)ac;
	(void)av;
	env_list = ft_env_to_list(env);
	while (1)
	{
		test = readline("Test readline :");
		if (ft_strcmp(test, "test") == 0)
		{
			free(test);
			exit (1);
		}
		verif = ft_get_args(test);
		temp = verif;
		if (verif != NULL)
		{
			ft_set_token(verif);
			while (verif != NULL)
			{
				verif = ft_get_infile(verif);
				verif = ft_get_heredoc(verif);
				verif = ft_get_outfile(verif);
				verif = ft_get_appendout(verif);
				ft_join_cmd(verif);
				if (ft_test(verif, env_list) == -1)
				{
					printf("Missing or extra dquote\n");
					break;
				}
				printf("final content = %s,  token = %d\n", verif->content, verif->token);
				verif = verif->next;
			}
			ft_cleararg(temp);
		}
	}
	return (0);
}
