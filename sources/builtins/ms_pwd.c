/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 08:42:01 by aweaver           #+#    #+#             */
/*   Updated: 2022/08/02 09:32:00 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_pwd(int std[2])
{
	char	*cwd;
	char	*buff;
	int		i;

	i = 1;
	cwd = NULL;
	while (cwd == NULL)
	{
		buff = ft_magic_malloc(MALLOC, sizeof(*buff) * i, NULL);
		cwd = getcwd(buff, i);
		if (cwd == NULL)
		{
			i++;
			buff = ft_magic_malloc(FREE, 0, buff);
			if (i > 4096)
			{
				ft_eprintf(MS_NOCWD MS_NOCWD2);
				close(std[0]);
				close(std[1]);
				rl_clear_history();
				ft_magic_malloc(FLUSH, errno, NULL);
			}
		}
	}
	return (buff);
}

int	ft_print_pwd(int std[2])
{
	char	*pwd;

	pwd = ft_get_pwd(std);
	printf("%s\n", pwd);
	pwd = ft_magic_malloc(FREE, 0, pwd);
	return (0);
}
