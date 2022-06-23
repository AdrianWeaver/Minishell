/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 08:42:01 by aweaver           #+#    #+#             */
/*   Updated: 2022/06/23 14:16:12 by aweaver          ###   ########.fr       */
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
		buff = ft_magic_malloc(MALLOC, sizeof(*cwd) * i, NULL);
		cwd = getcwd(buff, i);
		if (cwd == NULL)
		{
			i++;
			buff = ft_magic_malloc(FREE, 0, buff);
		}
	}
	return (buff);
}

void	ft_print_pwd(void)
{
	char	*pwd;

	pwd = ft_get_pwd();
	printf("%s\n", pwd);
	pwd = ft_magic_malloc(FREE, 0, pwd);
}
