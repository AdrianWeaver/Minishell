/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:18:40 by aweaver           #+#    #+#             */
/*   Updated: 2022/04/13 15:45:36 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	(void)envp;
	(void)ac;
	(void)av;
	char 	*test;
	t_arg	*verif;

	test = readline("Test readline :");
	verif = ft_get_args(test);
	ft_set_token(verif);
	printf("%s\n", verif->token);
	free(test);
	ft_cleararg(verif);
	return (0);
}
