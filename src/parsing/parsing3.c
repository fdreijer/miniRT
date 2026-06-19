/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:59:25 by hkonstan          #+#    #+#             */
/*   Updated: 2026/06/19 16:17:12 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_light(char **s, t_light *l)
{
	static int	i = 0;

	if (i)
		return (0);
	i = 1;
	if (!s || !s[0] || !s[1] || !s[2] || !s[3] || s[4])
		return (0);
	if (!parse_vector(s[1], &(l->pos)))
		return (0);
	l->brightness = ft_atof(s[2]);
	if (l->brightness == INFINITY || l->brightness < 0 || l->brightness > 1)
		return (0);
	if (!parse_color(s[3], &(l->color)))
		return (0);
	return (1);
}

int	is_object(char *str)
{
	return (!ft_strcmp(str, "pl") || !ft_strcmp(str, "sp") \
|| !ft_strcmp(str, "cy"));
}

int	add_object(t_scene *scene, void	*obj, t_type type)
{
	t_object	*object;
	t_object	*head;

	object = ft_calloc(1, sizeof(t_object));
	if (!object)
		return (0);
	object->type = type;
	object->object = obj;
	head = scene->all_objects;
	while (head && head->next)
		head = head->next;
	if (!head)
		scene->all_objects = object;
	else
		head->next = object;
	return (1);
}

int	parse_sphere(t_scene *scene, char **s)
{
	t_sphere	*sp;

	if (!s || !s[0] || !s[1] || !s[2] || !s[3] || s[4])
		return (0);
	sp = ft_calloc(1, sizeof(t_sphere));
	if (!sp)
		return (0);
	if (!parse_vector(s[1], &(sp->pos)))
		return (free(sp), 0);
	sp->diameter = ft_atof(s[2]);
	if (sp->diameter == INFINITY || sp->diameter <= 0)
		return (free(sp), 0);
	if (!parse_color(s[3], &(sp->color)))
		return (free(sp), 0);
	if (!add_object(scene, sp, SPHERE))
		return (free(sp), 0);
	return (1);
}
