/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects_cylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:48:27 by hkonstan          #+#    #+#             */
/*   Updated: 2026/06/11 17:26:37 by fdreijer         ###   ########.fr       */
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
	normal = v_normalize(v_sub(v_add(ray.origin, v_scale(ray.dir, intersection->distance)), cl->pos));
	light_dir = v_normalize(v_sub(scene->light.pos, intersection_point));
	intersection->angle = v_dot(normal, light_dir);
	if (intersection->angle < 0)
		intersection->angle = 0;
	ray_obstructed(scene, intersection_point, this, intersection);
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

void	angle_cl_plane(t_scene *scene, t_ray ray, \
t_object *this, t_intersection *intersection)
{
	t_cylinder	*cl;
	t_vector	intersect_point;
	t_vector	normal;
	t_vector	light_dir;
	double		dot_normal_ray;

	cl = (t_cylinder *)this->object;
	intersect_point = v_add(ray.origin, \
v_scale(ray.dir, intersection->distance));
	light_dir = v_normalize(v_sub(scene->light.pos, intersect_point));
	dot_normal_ray = v_dot(cl->normal, ray.dir);
	if (dot_normal_ray > 0)
		normal = v_scale(cl->normal, -1.0);
	else
		normal = cl->normal;
	intersection->angle = v_dot(normal, light_dir);
	if (intersection->angle < 0)
		intersection->angle = 0;
	ray_obstructed(scene, intersect_point, this, intersection);
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
	if (hit_distance > 0 && hit_distance < intersection->distance
			&& hit_cap(cl, ray, hit_distance, plane_center))
		intersection->distance = hit_distance;
	plane_normal = v_scale(cl->normal, -1.0);
	plane_center = v_add(cl->pos, v_scale(plane_normal, cl->height / 2.0));
	hit_distance = -v_dot(v_sub(ray.origin, plane_center), plane_normal)
		/ v_dot(ray.dir, plane_normal);
	if (hit_distance > 0 && hit_distance < intersection->distance
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
	intersects_cylinder_plane(ray, this, intersection);
	if (hit != intersection->distance)
		return (1);
	return (0);
}

//void	angle_cylinder(t_scene *scene, t_ray ray, \
//t_object *this, t_intersection *intersection)
//{
//	if (intersects_cylinder_plane(ray, this, intersection))
//		angle_cl_plane(scene, ray, this, intersection);
//	else
//		angle_cylinder_wall(scene, ray, this, intersection);
//}

void	angle_cylinder(t_scene *scene, t_ray ray, \
t_object *this, t_intersection *intersection)
{
	t_cylinder	*cl;
	t_vector	p;
	t_vector	normal;
	t_vector	light_dir;
	double		h;

	cl = (t_cylinder *)this->object;
	p = v_add(ray.origin, v_scale(ray.dir, intersection->distance));
	h = v_dot(v_sub(p, cl->pos), cl->normal);
	if (h == cl->height / 2.0){
		if (v_dot(cl->normal, ray.dir) > 0)
			normal = v_scale(cl->normal, -1.0);
		else
			normal = cl->normal;
	}
	else{
		t_vector	v = v_sub(p, cl->pos);
		t_vector	vperp = v_sub(v, v_scale(cl->normal, v_dot(v, cl->normal)));
		normal = v_normalize(vperp);
	}
	
	light_dir = v_normalize(v_sub(scene->light.pos, p));
	intersection->angle = v_dot(normal, light_dir);
	if (intersection->angle < 0)
		intersection->angle = 0;
	ray_obstructed(scene, p, this, intersection);
}