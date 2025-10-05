/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:26:49 by kali              #+#    #+#             */
/*   Updated: 2025/10/05 18:04:09 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_lights(t_light *lights)
{
	t_light *next;
	
	while (lights)
	{
		next = lights->next;
		free(lights);
		lights = next;
	}
}

void	free_planes(t_plane *planes)
{
	t_plane	*next;

	while (planes)
	{
		next = planes->next;
		free(planes->material);
		free(planes);
		planes = next;
	}
}

void	free_materials(t_object *objects)
{
	while (objects)
	{
		if (objects->type == SPHERE)
			free(((t_sphere *)(objects->object))->material);
		if (objects->type == CYLINDER)
			free(((t_cylinder *)(objects->object))->material);
		objects = objects->next;
	}
}

void	free_objects(t_object *objects)
{
	t_object *next;

	while (objects)
	{
		next = objects->next;
		free(objects->object);
		free(objects);
		objects = next;
	}
}

void	free_scene_exit(t_scene	*scene, char *msg, int val)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	free_lights(scene->lights);
	free_planes(scene->grid.planes);
	free_materials(scene->all_objects);
	free_objects(scene->all_objects);
	//TODO free VOXELS
	free(scene);
	exit(val);
}