/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:11:12 by kali              #+#    #+#             */
/*   Updated: 2026/06/19 16:18:17 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_vector(char *str, t_vector *v)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (free_split(split), 0);
	v->x = ft_atof(split[0]);
	v->y = ft_atof(split[1]);
	v->z = ft_atof(split[2]);
	free_split(split);
	if (v->x == INFINITY || v->y == INFINITY || v->z == INFINITY)
		return (0);
	return (1);
}

int	check_normal(t_vector *v)
{
	if (sqrt(v_dot(*v, *v)) < 1e-9)
		return (0);
	*v = v_normalize(*v);
	return (1);
}

int	parse_color(char *str, t_color *c)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (free_split(split), 0);
	c->r = ft_atoi(split[0]);
	c->g = ft_atoi(split[1]);
	c->b = ft_atoi(split[2]);
	free_split(split);
	if (c->r < 0 || c->r > 255 || c->g < 0 || c->g > 255 || c->b < 0 || \
c->b > 255)
		return (0);
	return (1);
}

int	parse_ambient(char **s, t_ambient *a)
{
	static int	i = 0;

	if (i)
		return (0);
	i = 1;
	if (!s || !s[0] || !s[1] || !s[2] || s[3])
		return (0);
	a->ratio = ft_atof(s[1]);
	if (a->ratio == INFINITY || a->ratio < 0 || a->ratio > 1)
		return (0);
	if (!parse_color(s[2], &(a->color)))
		return (0);
	return (1);
}

int	parse_camera(char **s, t_camera *c)
{
	static int	i = 0;

	if (i)
		return (0);
	i = 1;
	if (!s || !s[0] || !s[1] || !s[2] || !s[3] || s[4])
		return (0);
	if (!parse_vector(s[1], &(c->pos)))
		return (0);
	if (!parse_vector(s[2], &(c->normal)))
		return (0);
	if (!check_normal(&c->normal))
		return (0);
	if (c->normal.y == 1 || c->normal.y == -1)
		c->normal.z = 0.0001;
	c->fov = ft_atof(s[3]);
	if (c->fov == INFINITY || c->fov < 0 || c->fov > 180)
		return (0);
	c->right = v_normalize(v_cross(c->normal, (t_vector){0, 1, 0}));
	c->up = v_normalize(v_cross(c->right, c->normal));
	c->tan_half_fov = tan(c->fov * 0.5 * PI / 180.0);
	return (1);
}
