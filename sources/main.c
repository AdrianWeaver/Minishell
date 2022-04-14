/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:18:40 by aweaver           #+#    #+#             */
/*   Updated: 2022/04/14 16:45:39 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	char	*test;
	t_arg	*verif;

	(void)envp;
	(void)ac;
	(void)av;
	test = readline("Test readline :");
	verif = ft_get_args(test);
	ft_set_token(verif);
	while (verif != NULL)
	{
		printf("content = %s,  token = %s\n", verif->content, verif->token);
		verif = verif->next;
	}
	return (0);
}
