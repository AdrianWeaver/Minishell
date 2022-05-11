/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervoni <jcervoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:00:46 by jcervoni          #+#    #+#             */
/*   Updated: 2022/05/11 17:43:22 by jcervoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_reasy_to_expand(t_arg *arg)
{
	char	**temp;
	int		i;

	i = 1;
	while(arg->content[i] != '\0')
	{
		if (arg->content[i] == '$')
			i++;
	}
	if (i > 1)
	{
		temp = malloc(sizeof(char *) * i + 2);
		if (temp == NULL)
			return (NULL);
	}
}

// void ft_expand(t_arg *arg, t_env *env, char ** temp)
// {
// 	int	i;
// 	int	j;
// 	int	t;

// 	i = 0;
// 	j = 0;
// 	t = 0;
// 	while (arg->content[i] != '\0')
// 	{
// 		if (arg->content[i] == '$' && (ft_isalnum(arg->content[i + 1]) == 1
// 			|| arg->content[i + 1] == '_'))
// 		{
// 			temp[t] = ft_substr(arg->content, j, i - j);
// 			t++;
// 			j = i + 1;
// 			while 
// 		}
// 		i++;
		
// 	}
// }