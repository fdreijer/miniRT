/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:55:28 by fdreijer          #+#    #+#             */
/*   Updated: 2025/10/04 18:07:51 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *oldptr, int oldsize, int newsize)
{
	void	*newptr;

	if (oldsize < 0 || newsize < 0)
		return (NULL);
	if (oldptr == NULL)
		return (ft_calloc(newsize, sizeof(char)));
	if (newsize == 0)
		return (free(oldptr), NULL);
	newptr = ft_calloc(newsize, sizeof(char));
	if (!newptr)
		return (free(oldptr), NULL);
	if (newsize > oldsize)
		ft_memmove(newptr, oldptr, oldsize);
	else
		ft_memmove(newptr, oldptr, newsize);
	free(oldptr);
	return (newptr);
}
