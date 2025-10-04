/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:12:33 by fdreijer          #+#    #+#             */
/*   Updated: 2025/10/04 18:07:56 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	countwords(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 1;
	if (*s == 0)
		return (0);
	while (s[i])
	{
		if (i > 0 && s[i] == c && s[i - 1] != c)
			count++;
		if (s[i + 1] == 0 && s[i] == c)
			count--;
		i++;
	}
	return (count);
}

static	char	*fill_out(char const *s, char c)
{
	size_t	i;
	char	*out;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	out = ft_calloc(sizeof(char), (i + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		out[i] = s[i];
		i++;
	}
	out[i] = 0;
	return (out);
}

static void	free_split(char **split, int len)
{
	while (--len >= 0)
		free(split[len]);
	free(split);
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	size_t	i;
	int		w;

	if (!s)
		return (NULL);
	i = 0;
	w = -1;
	out = ft_calloc(sizeof(char *), (countwords(s, c) + 1));
	if (!out)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			out[++w] = fill_out(s + i, c);
			if (!out[w])
				return (free_split(out, w), NULL);
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (out);
}
