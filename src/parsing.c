/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:11:12 by kali              #+#    #+#             */
/*   Updated: 2026/01/06 18:52:12 by kali             ###   ########.fr       */
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

int	check_normal(t_vector v)
{
	double	len;

	if (!v_in_bounds(v, -1.0, 1.0))
		return (0);
	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (fabs(len - 1) > 1e-6)
		return (0);
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
	if (!s || !s[0] || !s[1] || !s[2] || !s[3] || s[4])
		return (0);
	if (!parse_vector(s[1], &(c->pos)))
		return (0);
	if (!parse_vector(s[2], &(c->normal)))
		return (0);
	if (!check_normal(c->normal))
		return (0);
	c->fov = ft_atof(s[3]);
	if (c->fov == INFINITY || c->fov < 0 || c->fov > 180)
		return (0);
	return (1);
}

int	parse_light(char **s, t_light *l)
{
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

int	parse_cylinder(t_scene *scene, char **s)
{
	t_cylinder	*c;

	if (!s || !s[0] || !s[1] || !s[2] || !s[3] || !s[4] || !s[5] || s[6])
		return (0);
	c = ft_calloc(1, sizeof(t_cylinder));
	if (!c)
		return (0);
	if (!parse_vector(s[1], &(c->pos)))
		return (free(c), 0);
	if (!parse_vector(s[2], &(c->normal)) || !check_normal(c->normal))
		return (free(c), 0);
	c->diameter = ft_atof(s[3]);
	c->height = ft_atof(s[4]);
	if (c->diameter == INFINITY || c->diameter < 0 \
|| c->height == INFINITY || c->height < 0 || !parse_color(s[5], &(c->color)))
		return (free(c), 0);
	if (!add_object(scene, c, CYLINDER))
		return (free(c), 0);
	return (1);
}

int	parse_plane(t_scene *scene, char **s)
{
	t_plane	*p;

	if (!s || !s[0] || !s[1] || !s[2] || !s[3] || s[4])
		return (0);
	p = ft_calloc(1, sizeof(t_plane));
	if (!parse_vector(s[1], &(p->pos)))
		return (free(p), 0);
	if (!parse_vector(s[2], &(p->normal)) || !check_normal(p->normal))
		return (free(p), 0);
	if (!parse_color(s[3], &(p->color)))
		return (free(p), 0);
	if (!add_object(scene, p, PLANE))
		return (free(p), 0);
	return (1);
}

int	parse_object(t_scene *scene, char **s)
{
	if (!s || !s[0])
		return (0);
	if (!ft_strcmp(s[0], "sp"))
		return (parse_sphere(scene, s));
	if (!ft_strcmp(s[0], "pl"))
		return (parse_plane(scene, s));
	if (!ft_strcmp(s[0], "cy"))
		return (parse_cylinder(scene, s));
	return (0);
}

void	parse_line(t_scene *scene, char *line)
{
	char	**s;

	if (!line || line[0] == '#' )
		return ;
	s = split_space(line);
	if (!s || !s[0])
		return (free_split(s));
	else if (!ft_strcmp(s[0], "A") && !parse_ambient(s, &(scene->ambient)))
		return (free_split(s), free_scene_exit(scene, "invalid ambient\n", 1));
	else if (!ft_strcmp(s[0], "C") && !parse_camera(s, &(scene->cam)))
		return (free_split(s), free_scene_exit(scene, "invalid camera\n", 1));
	else if (!ft_strcmp(s[0], "L") && !parse_light((s), &(scene->light)))
		return (free_split(s), free_scene_exit(scene, "invalid light\n", 1));
	else if (is_object(s[0]) && !parse_object(scene, s))
		return (free_split(s), free_scene_exit(scene, "invalid object\n", 1));
	else if (ft_strcmp(s[0], "L") && ft_strcmp(s[0], "C") && \
ft_strcmp(s[0], "A") && !is_object(s[0]))
		return (free_split(s), free_scene_exit(scene, "invalid line\n", 1));
	free_split(s);
}

void	parse_file(t_scene *scene, char *scene_file)
{
	char	*line;
	int		fd;

	fd = open(scene_file, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		parse_line(scene, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
