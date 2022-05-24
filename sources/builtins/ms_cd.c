/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:04:22 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/24 13:49:39 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_env *env, char *path)
{
	char	*cwd;		
	char	*buff;
	int		i;

	i = 1;
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
	printf("%s\n", cwd);
	printf("%s\n", buff);
	free(cwd);
}

int main(void)
{
	ft_cd(NULL, NULL);
	return (0);
}
