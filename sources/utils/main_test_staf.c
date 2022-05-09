/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_staf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:50:56 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/09 19:01:53 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

void	ft_free_env(t_env **env_start);
t_env		*ft_get_env_element(char *env_line);
t_env		**ft_env_to_list(char **env);

int	main(int argc, char **argv, char **env)
{
	t_env	**env_list;
	t_env	*env_start;
	(void)env_list;
	(void)argc;
	(void)argv;

	env_list = ft_env_to_list(env);
	env_start = *env_list;
	while (*env_list)
	{
		printf("name = %s\n", (*env_list)->name);
		printf("content:\n");
		while (*(*env_list)->content)
		{
			printf("%s\n", *(*env_list)->content);
			(*env_list)->content++;
		}
		*env_list = (*env_list)->next;
	}
	ft_free_env(&env_start);
	return (0);
}
