/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:17:40 by fdreijer          #+#    #+#             */
/*   Updated: 2025/10/04 18:08:08 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int n)
{
	char	*dup;
	int		i;

	i = 0;
	dup = ft_calloc(ft_min(n, ft_strlen(str)) + 1, sizeof(char));
	if (!dup)
		return (NULL);
	while (str[i] && i < n)
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}
