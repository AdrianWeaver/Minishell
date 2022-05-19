/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_staf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:50:56 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/19 11:44:40 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	char	**unset_tester;
	char	**export_tester;
	int		ret;
	int		export_ret;

	(void)argc;
	(void)argv;
	unset_tester = ft_split("_toto", ' ');
	export_tester = ft_split("wesh+=nan wesh=jesuis:un:path wesh2 wesh3=", ' ');
	env_list = ft_env_to_list(env);
	ret = ft_unset(&env_list, unset_tester);
	export_ret = ft_export(env_list, export_tester);
	ft_print_env(env_list);
	ft_free_env(env_list);
	ft_free_double_array(unset_tester);
	ft_free_double_array(export_tester);
	printf("\33[0;32mUnset returned : %d\n\33[0m", ret);
	printf("\33[0;32mexport returned : %d\n\33[0m", export_ret);
	return (0);
}
