/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:12:39 by fdreijer          #+#    #+#             */
/*   Updated: 2025/10/04 18:07:42 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)dest;
	s2 = (unsigned char *)src;
	if (s1 > s2)
	{
		while (n)
		{
			*(s1 + n - 1) = *(s2 + n - 1);
			n--;
		}
	}
	else
	{
		while (n)
		{
			*s1 = *s2;
			s1++;
			s2++;
			n--;
		}
	}
	return (dest);
}
