/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:46:52 by kali              #+#    #+#             */
/*   Updated: 2026/06/11 15:39:17 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	v_normalize(t_vector v)
{
	double	mag;

	mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (!mag)
		return (v);
	return ((t_vector){v.x / mag, v.y / mag, v.z / mag});
}

t_vector	v_cross(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.y * v2.z - v1.z * v2.y, \
v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x});
}

t_vector	v_max(t_vector v1, t_vector v2)
{
	return ((t_vector){ft_max(v1.x, v2.x), \
ft_max(v1.y, v2.y), ft_max(v1.z, v2.z)});
}

t_vector	v_min(t_vector v1, t_vector v2)
{
	return ((t_vector){ft_min(v1.x, v2.x), \
ft_min(v1.y, v2.y), ft_min(v1.z, v2.z)});
}
