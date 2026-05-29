/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:30:22 by fdreijer          #+#    #+#             */
/*   Updated: 2026/05/29 15:00:47 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ray_obstructed(t_scene *scene, t_vector point, \
t_object *this, t_intersection *intersection)
{
	t_object		*obj;
	t_ray			light_ray;
	t_intersection	light_intersection;
	t_vector		light_dir;

	light_dir = v_sub(scene->light.pos, point);
	obj = scene->all_objects;
	light_ray.origin = point;
	light_ray.dir = v_normalize(v_sub(scene->light.pos, point));
	while (obj)
	{
		light_intersection.angle = 1;
		if (this != obj && g_intersects[obj->type](scene, light_ray, obj, \
&light_intersection) && light_intersection.distance \
< sqrt(v_dot(light_dir, light_dir)))
		{
			intersection->angle = 0;
			return ;
		}
		obj = obj->next;
	}
}

void	angle_sphere(t_scene *scene, t_ray ray, \
t_object *this, t_intersection *intersection)
{
	t_sphere	*sp;
	t_vector	intersect_point;
	t_vector	normal;
	t_vector	light_dir;

	sp = (t_sphere *)this->object;
	intersect_point = v_add(ray.origin, \
v_scale(ray.dir, intersection->distance));
	normal = v_normalize(v_sub(intersect_point, sp->pos));
	light_dir = v_normalize(v_sub(scene->light.pos, intersect_point));
	intersection->angle = v_dot(normal, light_dir);
	if (intersection->angle < 0)
		intersection->angle = 0;
	ray_obstructed(scene, intersect_point, this, intersection);
}

int	intersects_sphere(t_scene *scene, t_ray ray, \
t_object *this, t_intersection *intersection)
{
	t_sphere	*sp;
	t_vector	oc;
	double		b;
	double		c;
	double		discriminant;

	sp = (t_sphere *)this->object;
	oc = v_sub(ray.origin, sp->pos);
	b = 2 * v_dot(oc, ray.dir);
	c = v_dot(oc, oc) - ((sp->diameter / 2.0f) * (sp->diameter / 2.0f));
	discriminant = b * b - 4.0 * c;
	if (((-b + sqrt(discriminant)) / 2.0f) > 0 && \
((-b - sqrt(discriminant)) / 2.0f) > 0)
		intersection->distance = fmin(-b + sqrt(discriminant) \
/ 2.0f, (-b - sqrt(discriminant)) / 2.0f);
	else
		intersection->distance = fmax(-b + sqrt(discriminant) \
/ 2.0f, (-b - sqrt(discriminant)) / 2.0f);
	if (intersection->distance <= 0)
		return (0);
	if (!intersection->angle)
		angle_sphere(scene, ray, this, intersection);
	return (1);
}

void	angle_plane(t_scene *scene, t_ray ray, \
t_object *this, t_intersection *intersection)
{
	t_plane		*pl;
	t_vector	intersect_point;
	t_vector	normal;
	t_vector	light_dir;
	double		dot_normal_ray;

	pl = (t_plane *)this->object;
	intersect_point = v_add(ray.origin, \
v_scale(ray.dir, intersection->distance));
	light_dir = v_normalize(v_sub(scene->light.pos, intersect_point));
	dot_normal_ray = v_dot(pl->normal, ray.dir);
	if (dot_normal_ray > 0)
		normal = v_scale(pl->normal, -1.0);
	else
		normal = pl->normal;
	intersection->angle = v_dot(normal, light_dir);
	if (intersection->angle < 0)
		intersection->angle = 0;
	ray_obstructed(scene, intersect_point, this, intersection);
}

int	intersects_plane(t_scene *scene, t_ray ray, \
t_object *this, t_intersection *intersection)
{
	t_plane	*p;

	p = (t_plane *)this->object;
	intersection->distance = -v_dot(v_sub(ray.origin, p->pos), p->normal) \
/ v_dot(ray.dir, p->normal);
	if (intersection->distance <= 0)
		return (0);
	if (!intersection->angle)
		angle_plane(scene, ray, this, intersection);
	return (1);
}

// void	angle_cylinder_plane(t_scene *scene, t_ray ray, \
// t_object *this, t_intersection *intersection)
// {
// 	t_cylinder	*cl;
// 	t_vector	intersect_point;
// 	t_vector	normal;
// 	t_vector	light_dir;

// 	cl = (t_cylinder *)this->object;
// 	intersect_point = v_add(ray.origin, \
// v_scale(ray.dir, intersection->distance));
// 	normal = v_normalize(v_sub(intersect_point, cl->pos));
// 	light_dir = v_normalize(v_sub(scene->light.pos, intersect_point));
// 	intersection->angle = v_dot(normal, light_dir);
// 	if (intersection->angle < 0)
// 		intersection->angle = 0;
// 	ray_obstructed(scene, intersect_point, this, intersection);
// }

void get_cl_quadratic(t_cylinder *cl, t_ray ray)
{
	t_vector	oc;
	t_vector	dir_parallel;
	t_vector	oc_parallel;

	oc = v_sub(ray.origin, cl->pos);
	dir_parallel = v_scale(v_normalize(cl->normal), v_dot(ray.dir, v_normalize(cl->normal)));
	oc_parallel = v_scale(v_normalize(cl->normal), v_dot(oc, v_normalize(cl->normal)));
	cl->q.dir_perp = v_sub(ray.dir, dir_parallel);
	cl->q.oc_perp = v_sub(oc, oc_parallel);
	cl->q.a = v_dot(cl->q.dir_perp, cl->q.dir_perp);
	cl->q.b = 2 * v_dot(cl->q.oc_perp, cl->q.dir_perp);
	cl->q.c = v_dot(cl->q.oc_perp, cl->q.oc_perp) - (cl->diameter / 2.0f) * (cl->diameter / 2.0f);
	cl->q.discriminant = cl->q.b * cl->q.b - 4.0 * cl->q.a * cl->q.c;
}

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

void	angle_cylinder_wall(t_scene *scene, t_ray ray,
	t_object *this, t_intersection *intersection)
{
	t_cylinder	*cl;
	t_vector	intersection_point;
	t_vector	normal;
	t_vector	light_dir;

	cl = (t_cylinder *)this->object;
	intersection_point = v_add(ray.origin,
			v_scale(ray.dir, intersection->distance));
	normal = v_normalize(v_sub(intersection_point, cl->pos));
	light_dir = v_normalize(v_sub(scene->light.pos, intersection_point));
	intersection->angle = v_dot(normal, light_dir);
	if (intersection->angle < 0)
		intersection->angle = 0;
	ray_obstructed(scene, intersection_point, this, intersection);
}

int	hit_cap(double diameter, t_ray ray, double i_d, t_vector plane_c)
{
	t_vector	p;
	t_vector	d;
	double		from_center;

	p = v_add(ray.origin, v_scale(ray.dir, i_d));
	d = v_sub(p, plane_c);
	from_center = sqrt(v_dot(d, d));
	if (diameter / 2.0f >= from_center)
		return (1);
	return (0);
}

void	intersects_cylinder_plane(t_scene *scene, t_ray ray,
	t_object *this, t_intersection *intersection)
{
	t_cylinder	*cl;
	t_vector	plane_normal;
	t_vector	plane_center;

	cl = (t_cylinder *)this->object;
	plane_normal = cl->normal;
	plane_center = v_add(cl->pos, v_scale(cl->normal, cl->height / 2.0));
	if (-v_dot(v_sub(ray.origin, plane_center), plane_normal)
		/ v_dot(ray.dir, plane_normal) > 0)
	{
		if (hit_cap(cl->diameter, ray, intersection->distance, plane_center))
			angle_plane(scene, ray, this, intersection);
	}
	plane_normal = v_scale(cl->normal, -1.0);
	plane_center = v_add(cl->pos, v_scale(cl->normal, cl->height / 2.0));
	if (-v_dot(v_sub(ray.origin, plane_center), plane_normal)
		/ v_dot(ray.dir, plane_normal) > 0)
	{
		if (hit_cap(cl->diameter, ray, intersection->distance, plane_center))
			angle_plane(scene, ray, this, intersection);
	}
}

int	intersects_cylinder(t_scene *scene, t_ray ray, \
t_object *this, t_intersection *intersection)
{
	t_cylinder	*cl;
	double		sqrt_disc;

	cl = (t_cylinder *)this->object;
	get_cl_quadratic(cl, ray);
	if (cl->q.a <= 0 || cl->q.discriminant < 0)
		return (0);
	sqrt_disc = sqrt(cl->q.discriminant);
	cl->q.t1 = (-cl->q.b + sqrt_disc) / (2.0 * cl->q.a);
	cl->q.t2 = (-cl->q.b - sqrt_disc) / (2.0 * cl->q.a);
	if (hits_cl_wall(ray, cl, cl->q.t1) && hits_cl_wall(ray, cl, cl->q.t2))
		intersection->distance = fmin(cl->q.t1, cl->q.t2);
	else if (hits_cl_wall(ray, cl, cl->q.t1))
		intersection->distance = cl->q.t1;
	else if (hits_cl_wall(ray, cl, cl->q.t2))
		intersection->distance = cl->q.t2;
	else
		return (0);
	if (!intersection->angle)
		angle_cylinder_wall(scene, ray, this, intersection);
	intersects_cylinder_plane(scene, ray, this, intersection);
	return (1);
}
