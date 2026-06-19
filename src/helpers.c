/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:36:50 by fdreijer          #+#    #+#             */
/*   Updated: 2026/06/19 16:16:24 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	get_color_sphere(t_object *object)
{
	t_sphere	*sp;

	sp = (t_sphere *)object->object;
	return (sp->color);
}

t_color	get_color_cylinder(t_object *object)
{
	t_cylinder	*c;

	c = (t_cylinder *)object->object;
	return (c->color);
}

t_color	get_color_plane(t_object *object)
{
	t_plane	*p;

	p = (t_plane *)object->object;
	return (p->color);
}

void	get_cl_quadratic(t_cylinder *cl, t_ray ray)
{
	t_vector	oc;
	t_vector	dir_parallel;
	t_vector	oc_parallel;

	oc = v_sub(ray.origin, cl->pos);
	dir_parallel = v_scale(cl->normal,
			v_dot(ray.dir, cl->normal));
	oc_parallel = v_scale(cl->normal, v_dot(oc, cl->normal));
	cl->q.dir_perp = v_sub(ray.dir, dir_parallel);
	cl->q.oc_perp = v_sub(oc, oc_parallel);
	cl->q.a = v_dot(cl->q.dir_perp, cl->q.dir_perp);
	cl->q.b = 2 * v_dot(cl->q.oc_perp, cl->q.dir_perp);
	cl->q.c = v_dot(cl->q.oc_perp, cl->q.oc_perp)
		- (cl->diameter / 2.0f) * (cl->diameter / 2.0f);
	cl->q.discriminant = cl->q.b * cl->q.b - 4.0 * cl->q.a * cl->q.c;
}
