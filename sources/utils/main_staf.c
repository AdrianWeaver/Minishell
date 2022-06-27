/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_staf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <aweaver@42.fr>                     +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:14:06 by aweaver           #+#    #+#             */
/*   Updated: 2022/06/23 13:55:05 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	main(void)
{
	int	*test;
	int	*test2;
	int	*test3;
	int	*test4;
	int	*test_hard;

	test_hard = malloc(12);
	test = ft_magic_malloc(MALLOC, (sizeof(*test) * 1), NULL);
	test2 = ft_magic_malloc(MALLOC, (sizeof(*test2) * 1), NULL);
	test3 = ft_magic_malloc(MALLOC, (sizeof(*test3) * 1), NULL);
	test4 = ft_magic_malloc(MALLOC, (sizeof(*test4) * 1280), NULL);
	test_hard = ft_magic_malloc(FREE, 0, test_hard);
	test2 = ft_magic_malloc(FREE, 0, test2);
	test = ft_magic_malloc(FREE, 0, test);
	test3 = ft_magic_malloc(FREE, 0, test3);
	test4 = ft_magic_malloc(FREE, 0, test4);
	return (0);
}
	//test = ft_magic_malloc(FLUSH, 0, NULL);
