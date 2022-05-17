/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_staf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:50:56 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/17 10:13:07 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

void	ft_free_env(t_env *env_start);
t_env		*ft_get_env_element(char *env_line);
t_env		*ft_env_to_list(char **env);

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	t_env	*env_start;
	int i;
	(void)env_list;
	(void)argc;
	(void)argv;

	char **unset_tester;
	unset_tester = ft_split("toto", ' ');
	env_list = ft_env_to_list(env);
	env_start = env_list;
	ft_unset(env_list, unset_tester);
	while (env_list)
	{
		i = 0;
		printf("%s", env_list->name);
		//printf("content:\n");
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
	return (0);
}
