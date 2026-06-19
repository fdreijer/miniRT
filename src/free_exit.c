/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:26:49 by kali              #+#    #+#             */
/*   Updated: 2026/06/19 15:18:46 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_objects(t_object *objects)
{
	t_object	*next;

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
	free_objects(scene->all_objects);
	free(scene);
	exit(val);
}

void free_exit (t_scene	*scene)
{
	free_objects(scene->all_objects);
	free(scene->image);
	free(scene->mlx);
	free(scene);
}
