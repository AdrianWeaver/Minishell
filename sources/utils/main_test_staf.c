/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_staf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:50:56 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/10 17:41:07 by aweaver          ###   ########.fr       */
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

	env_list = ft_env_to_list(env);
	env_start = env_list;
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
	return (0);
}
