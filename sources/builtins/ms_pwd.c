/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 08:42:01 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/25 11:37:21 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_pwd(void)
{
	char	*cwd;		
	char	*buff;
	int		i;

	i = 1;
	cwd = NULL;
	while (cwd == NULL)
	{
		buff = malloc(sizeof(*cwd) * i);
		cwd = getcwd(buff, i);
		if (cwd == NULL)
		{
			i++;
			free(buff);
		}
	}
	return (cwd);
}

void	ft_print_pwd(void)
{
	char	*pwd;

	pwd = ft_get_pwd();
	printf("%s\n", pwd);
	free (pwd);
}
