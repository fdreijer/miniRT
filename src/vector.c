/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:46:52 by kali              #+#    #+#             */
/*   Updated: 2025/10/05 16:46:37 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	v_add(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vector	v_sub(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vector	v_scale(t_vector v, double s)
{
	return ((t_vector){v.x * s, v.y * s, v.z * s});
}

int	v_in_bounds(t_vector v, double min, double max)
{
	return (v.x >= min && v.x <= max && v.y >= min && v.y <= max \
&& v.z >= min && v.z <= max);
}
