/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:17:52 by fdreijer          #+#    #+#             */
/*   Updated: 2025/10/04 18:08:05 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*s1p;
	const unsigned char	*s2p;

	s1p = (const unsigned char *)s1;
	s2p = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1p[i] == '\0' || s2p[i] == '\0')
		{
			return (s1p[i] - s2p[i]);
		}
		if (s1p[i] > s2p[i])
		{
			return (s1p[i] - s2p[i]);
		}
		if (s1p[i] < s2p[i])
		{
			return (s1p[i] - s2p[i]);
		}
		i++;
	}
	return (0);
}
