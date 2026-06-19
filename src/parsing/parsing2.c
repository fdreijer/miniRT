/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:58:43 by hkonstan          #+#    #+#             */
/*   Updated: 2026/06/19 16:21:34 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	if (!parse_vector(s[2], &(c->normal)) || !check_normal(&c->normal))
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
	if (!parse_vector(s[2], &(p->normal)) || !check_normal(&p->normal))
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

void	parse_line(t_scene *scene, char *line, int fd)
{
	char	**s;

	if (!line || line[0] == '#' )
		return ;
	s = split_space(line);
	if (!s || !s[0])
		return (free_split(s));
	else if (!ft_strcmp(s[0], "A") && !parse_ambient(s, &(scene->ambient)))
		return (free_split(s), free(line), free_scene_exit(scene,
				fd, "invalid ambient\n", 1));
	else if (!ft_strcmp(s[0], "C") && !parse_camera(s, &(scene->cam)))
		return (free_split(s), free(line), free_scene_exit(scene,
				fd, "invalid camera\n", 1));
	else if (!ft_strcmp(s[0], "L") && !parse_light((s), &(scene->light)))
		return (free_split(s), free(line), free_scene_exit(scene,
				fd, "invalid light\n", 1));
	else if (is_object(s[0]) && !parse_object(scene, s))
		return (free_split(s), free(line), free_scene_exit(scene,
				fd, "invalid object\n", 1));
	else if (ft_strcmp(s[0], "L") && ft_strcmp(s[0], "C") && \
ft_strcmp(s[0], "A") && !is_object(s[0]))
		return (free_split(s), free(line), free_scene_exit(scene,
				fd, "invalid line\n", 1));
	free_split(s);
}

int	parse_file(t_scene *scene, char *scene_file)
{
	char	*line;
	int		fd;

	fd = open(scene_file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(scene, line, fd);
		free(line);
		line = get_next_line(fd);
	}
	get_next_line(-1);
	close(fd);
	return (1);
}
