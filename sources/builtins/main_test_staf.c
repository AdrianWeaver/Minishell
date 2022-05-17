/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_staf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:50:56 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/17 14:20:18 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	int		i;
	char	**unset_tester;
	int		ret;

	(void)argc;
	(void)argv;
	unset_tester = ft_split("_toto", ' ');
	env_list = ft_env_to_list(env);
	ret = ft_unset(&env_list, unset_tester);
	ft_print_env(env_list);
	ft_free_env(env_list);
	ft_free_double_array(unset_tester);
	printf("\33[0;32mUnset returned : %d\n\33[0m", ret);
	return (0);
}
