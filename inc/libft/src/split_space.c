/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 09:45:58 by kali              #+#    #+#             */
/*   Updated: 2025/10/05 11:12:54 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i])
			count++;
		while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	return (count);
}

static char	*get_word(char **str)
{
	int		len;
	char	*word;

	len = 0;
	while ((*str)[len] && !ft_isspace((*str)[len]))
		len++;
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_memmove(word, *str, len);
	*str += len;
	return (word);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
}

char	**split_space(char *str)
{
	char	**split;
	int		count;
	
	count = 0;
	split = ft_calloc(count_words(str) + 1, sizeof(char *));
	if (!split)
		return NULL;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (*str)
		{
			split[count] =  get_word(&str);
			if (!split[count])
				return (free_split(split), NULL);
			count++;
		}
	}
	return (split);
}

// int main(void)
// {
// 	char **parts = split_space("cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255");
// 	for (int i = 0; parts[i]; i++)
// 		printf("part[%d] = \"%s\"\n", i, parts[i]);
// 	free_split(parts);
// }