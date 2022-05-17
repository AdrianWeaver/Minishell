/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_staf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:50:56 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/17 13:48:37 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	t_env	*env_start;
	int		i;
	char	**unset_tester;
	int		ret;

	(void)argc;
	(void)argv;
	unset_tester = ft_split("_toto", ' ');
	env_list = ft_env_to_list(env);
	ret = ft_unset(&env_list, unset_tester);
	env_start = env_list;
	while (env_list)
	{
		i = 0;
		printf("%s=", env_list->name);
		while (env_list->content[i])
		{
			printf("%s", env_list->content[i]);
			i++;
			if (env_list->content[i])
				printf(":");
		}
		env_list = env_list->next;
		printf("\n");
	}
	ft_free_env(env_start);
	ft_free_double_array(unset_tester);
	printf("\33[0;32mUnset returned : %d\n\33[0m", ret);
	return (0);
}
