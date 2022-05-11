/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:18:40 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/10 15:30:53 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	char	*test;
	t_arg	*verif;
	t_arg	*temp;

	(void)envp;
	(void)ac;
	(void)av;
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
			if (verif->token == TOKEN_CMD && verif->next != NULL)
				ft_join_cmd(verif);
			printf("content = %s,  token = %d\n", verif->content, verif->token);
			verif = verif->next;
		}
		ft_cleararg(temp);
	}
	return (0);
}
