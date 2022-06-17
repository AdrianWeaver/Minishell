/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:27:49 by aweaver           #+#    #+#             */
/*   Updated: 2022/01/05 19:05:05 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_count_words(char const *s, char c, size_t *j)
{
	size_t	in_a_word;
	size_t	word_count;

	*j = 0;
	in_a_word = 0;
	word_count = 0;
	while (*s)
	{
		if (in_a_word == 0 && *s != c)
			in_a_word = 1;
		if (in_a_word == 1 && (*s == c || *(s + 1) == 0))
		{
			in_a_word = 0;
			word_count++;
		}
		s++;
	}
	return (word_count);
}

static size_t	ft_custom_strlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static size_t	ft_check_malloc(char **tab, char *str, size_t index)
{
	if (!str && index != 0)
	{	
		while (index != 0)
		{
			free(tab[index - 1]);
			index--;
		}
		free(tab);
		return (0);
	}
	if (!str)
	{
		free(tab);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	word_count;
	size_t	i;
	size_t	j;
	size_t	word_length;

	i = -1;
	if (!s)
		return (0);
	word_count = ft_count_words(s, c, &j);
	tab = malloc(sizeof(*tab) * (word_count + 1));
	if (!tab)
		return (0);
	tab[word_count] = 0;
	while (++i < word_count)
	{
		while (s[j] == c)
			j++;
		word_length = ft_custom_strlen(&s[j], c);
		tab[i] = ft_substr(s, j, (word_length));
		j += word_length;
		if (ft_check_malloc(tab, tab[i], i) == 0)
			return (0);
	}
	return (tab);
}
