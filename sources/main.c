/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:18:40 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/12 14:15:24 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *env[])
{
	char	*test;
	t_arg	*verif;
	t_arg	*temp;
	// char	**var_count;
	// char	*var_ret;
	t_env	*env_list;
	// t_env	*env_start;
	// (void)env_list;
	(void)env;
	(void)ac;
	(void)av;

	env_list = ft_env_to_list(env);
	// env_start = env_list;
	while (1)
	{
		test = readline("Test readline :");
		if (ft_strcmp(test, "test") == 0)
		{
			free(test);
			exit (1);
		}
		verif = ft_get_args(test);
		ft_set_token(verif);
		temp = verif;
		while (verif != NULL)
		{
			verif = ft_get_infile(verif);
			verif = ft_get_heredoc(verif);
			verif = ft_get_outfile(verif);
			verif = ft_get_appendout(verif);
			ft_join_cmd(verif);
			// if (ft_check_dquotes(verif) == 0)
			// 	ft_remove_dquotes(verif);
			printf("content = %s,  token = %d\n", verif->content, verif->token);
			if (ft_test(verif, env_list) == -1)
			{
				printf("Missing or extra dquote\n");
				break;
			}
			// var_count = ft_count_expand(verif);
			// if (var_count != NULL)
			// 	ft_get_expanded(verif, env_list);
			verif = verif->next;
		}
		ft_cleararg(temp);
	}
	return (0);
}
