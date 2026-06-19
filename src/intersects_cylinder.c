/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects_cylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:48:27 by hkonstan          #+#    #+#             */
/*   Updated: 2026/06/19 16:22:05 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	hits_cl_wall(t_ray ray, t_cylinder *cl, double t)
{
	t_vector	p;
	double		h;

	if (t <= 0)
		return (0);
	p = v_add(ray.origin, v_scale(ray.dir, t));
	h = v_dot(v_sub(p, cl->pos), cl->normal);
	if (h < -cl->height / 2.0 || h > cl->height / 2.0)
		return (0);
	return (1);
}

double	hit_cap(t_cylinder *cl, t_ray ray, double i_d, t_vector plane_c)
{
	t_vector	p;
	t_vector	d;
	double		from_center;

	p = v_add(ray.origin, v_scale(ray.dir, i_d));
	d = v_sub(p, plane_c);
	from_center = sqrt(v_dot(d, d));
	if (cl->diameter / 2.0f >= from_center)
		return (1);
	return (0);
}

int	intersects_cylinder_plane(t_ray ray,
	t_object *this, t_intersection *intersection)
{
	t_cylinder	*cl;
	t_vector	plane_normal;
	t_vector	plane_center;
	double		hit_distance;
	double		hit;

	cl = (t_cylinder *)this->object;
	hit = intersection->distance;
	plane_normal = cl->normal;
	plane_center = v_add(cl->pos, v_scale(plane_normal, cl->height / 2.0));
	hit_distance = -v_dot(v_sub(ray.origin, plane_center), plane_normal)
		/ v_dot(ray.dir, plane_normal);
	if (hit_distance > 0 && hit_distance < intersection->distance \
&& hit_cap(cl, ray, hit_distance, plane_center))
		intersection->distance = hit_distance;
	plane_normal = v_scale(cl->normal, -1.0);
	plane_center = v_add(cl->pos, v_scale(plane_normal, cl->height / 2.0));
	hit_distance = -v_dot(v_sub(ray.origin, plane_center), plane_normal)
		/ v_dot(ray.dir, plane_normal);
	if (hit_distance > 0 && hit_distance < intersection->distance \
&& hit_cap(cl, ray, hit_distance, plane_center))
		intersection->distance = hit_distance;
	if (hit != intersection->distance)
		return (1);
	return (0);
}

int	intersects_cylinder(t_scene *scene, t_ray ray, \
t_object *this, t_intersection *intersection)
{
	t_cylinder	*cl;
	double		sqrt_disc;
	double		hit;
	int			obj;

	(void)scene;
	obj = 0;
	hit = intersection->distance;
	cl = (t_cylinder *)this->object;
	get_cl_quadratic(cl, ray);
	if (!(cl->q.a < 1e-6 || cl->q.discriminant < 0))
	{
		sqrt_disc = sqrt(cl->q.discriminant);
		cl->q.t = (-cl->q.b + sqrt_disc) / (2.0 * cl->q.a);
		if (hits_cl_wall(ray, cl, cl->q.t) && cl->q.t < intersection->distance)
			intersection->distance = cl->q.t;
		cl->q.t = (-cl->q.b - sqrt_disc) / (2.0 * cl->q.a);
		if (hits_cl_wall(ray, cl, cl->q.t) && cl->q.t < intersection->distance)
			intersection->distance = cl->q.t;
	}
	intersects_cylinder_plane(ray, this, intersection);
	if (hit != intersection->distance)
		return (1);
	return (0);
}

void	angle_cylinder(t_scene *scene, t_ray ray, \
t_object *this, t_intersection *intersection)
{
	t_cylinder	*cl;
	t_vector	p;
	t_vector	normal;
	t_vector	light_dir;
	double		s;

	cl = (t_cylinder *)this->object;
	p = v_add(ray.origin, v_scale(ray.dir, intersection->distance));
	s = v_dot(v_sub(p, cl->pos), cl->normal);
	if (fabs(s - cl->height / 2.0) < 1e-4)
		normal = v_scale(cl->normal, -1.0);
	else if (fabs(s + cl->height / 2.0) < 1e-4)
		normal = cl->normal;
	else
		normal = v_normalize(v_sub(v_sub(p, cl->pos), v_scale(cl->normal, \
v_dot(v_sub(p, cl->pos), cl->normal))));
	if (v_dot(normal, ray.dir) > 0)
		normal = v_scale(normal, -1.0);
	light_dir = v_normalize(v_sub(scene->light.pos, p));
	intersection->angle = v_dot(normal, light_dir);
	if (intersection->angle < 0)
		intersection->angle = 0;
	ray_obstructed(scene, p, intersection, normal);
}
