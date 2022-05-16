/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:18:40 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/16 18:16:39 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_set_token(verif);
		temp = verif;
		printf("debut, arg[0] = %c\n", verif->content[0]);
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
	return (0);
}
