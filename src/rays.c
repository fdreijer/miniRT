/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:37:40 by fdreijer          #+#    #+#             */
/*   Updated: 2026/06/19 16:16:05 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	generate_ray(t_scene *scene, int x, int y)
{
	t_ray	ray;
	float	horizontal;
	float	vertical;

	horizontal = (2.0 * x / WIDTH - 1.0) * ASPECT_RATIO;
	vertical = (1.0 - 2.0 * y / HEIGHT);
	ray.origin = scene->cam.pos;
	ray.dir = v_normalize(v_add(v_add(scene->cam.normal, \
v_scale(scene->cam.right, horizontal * scene->cam.tan_half_fov)), \
v_scale(scene->cam.up, vertical * scene->cam.tan_half_fov)));
	return (ray);
}

t_color	scale_color(t_scene *scene, t_color color, double angle)
{
	t_color	final_color;

	final_color.r = fmin(255.0, ((color.r / 255.0) * \
((scene->ambient.color.r / 255.0) * scene->ambient.ratio + \
(scene->light.color.r / 255.0) * angle * scene->light.brightness)) * 255.0);
	final_color.g = fmin(255.0, ((color.g / 255.0) * \
((scene->ambient.color.g / 255.0) * scene->ambient.ratio + \
(scene->light.color.g / 255.0) * angle * scene->light.brightness)) * 255.0);
	final_color.b = fmin(255.0, ((color.b / 255.0) * \
((scene->ambient.color.b / 255.0) * scene->ambient.ratio + \
(scene->light.color.b / 255.0) * angle * scene->light.brightness)) * 255.0);
	return (final_color);
}

t_object	*find_closest(t_scene *scene, t_ray ray, t_intersection *hit)
{
	t_object	*obj;
	t_object	*closest;
	double		distance;

	obj = scene->all_objects;
	closest = NULL;
	distance = INFINITY;
	while (obj)
	{
		hit->distance = INFINITY;
		if (g_intersects[obj->type](scene, ray, obj, hit)
			&& hit->distance < distance)
		{
			closest = obj;
			distance = hit->distance;
		}
		obj = obj->next;
	}
	hit->distance = distance;
	return (closest);
}

t_color	trace_ray(t_scene *scene, t_ray ray)
{
	t_color			color;
	t_object		*closest;
	t_intersection	hit;

	color = (t_color){0, 0, 0};
	closest = find_closest(scene, ray, &hit);
	if (closest)
	{
		g_get_angle[closest->type](scene, ray, closest, &hit);
		color = scale_color(scene, \
g_get_color[closest->type](closest), hit.angle);
	}
	return (color);
}

int	generate_rays(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	t_color	color;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			ray = generate_ray(scene, x, y);
			color = trace_ray(scene, ray);
			mlx_put_pixel(scene->image, x, y, \
(uint32_t)((color.r << 24) | (color.g << 16) | (color.b << 8) | 0xFF));
		}
	}
	return (0);
}
