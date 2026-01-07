/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:46:57 by kali              #+#    #+#             */
/*   Updated: 2026/01/07 00:22:41 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define HEIGHT 1250
# define WIDTH 2500

# define PI 3.1415926535

# include "libft/inc/libft.h"

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>

#include "MLX42.h"

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

typedef struct s_camera
{
	t_vector	pos;
	t_vector	normal;
	double		fov;
}				t_camera;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	dir;
}				t_ray;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}			t_ambient;

typedef struct s_light
{
	t_vector		pos;
	double			brightness;
	t_color			color;
}				t_light;

typedef enum e_texture
{
	NONE,
	CHECKERED,
	BUMP_MAP
}	t_texture;

typedef struct s_sphere
{
	t_vector	pos;
	double		diameter;
	t_color		color;
}				t_sphere;

typedef struct s_plane
{
	t_vector		pos;
	t_vector		normal;
	t_color			color;
	struct s_plane		*next;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	pos;
	t_vector	normal;
	double		diameter;
	double		height;
	t_color		color;
}				t_cylinder;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef struct s_intersection
{
	double		distance;
	double		angle;
}				t_intersection;

typedef struct s_object
{
	t_type			type;
	t_color			color;
	void			*object;
	struct s_object	*next;
}				t_object;

typedef struct s_scene
{
	t_camera		cam;
	t_ambient		ambient;
	t_light			light;
	t_object		*all_objects;
	mlx_t			*mlx;
	mlx_image_t		*image;
}					t_scene;


void		parse_file(t_scene *scene, char *scene_file);
t_vector	v_add(t_vector v1, t_vector v2);
t_vector	v_sub(t_vector v1, t_vector v2);
t_vector	v_scale(t_vector v, double s);
int			v_in_bounds(t_vector v, double min, double max);
double		v_dot(t_vector v1, t_vector v2);
t_vector	v_normalize(t_vector v);
t_vector	v_cross(t_vector v1, t_vector v2);

void		free_scene_exit(t_scene	*scene, char *msg, int val);

int			generate_rays(t_scene *scene);

int			intersects_sphere(t_scene *scene, t_ray ray, t_object *this, t_intersection *intersection);

typedef	int	(*intersects)(t_scene *scene ,t_ray ray, t_object *obj, t_intersection *intersection);

static const intersects	g_intersects[] = {
	[SPHERE] = intersects_sphere
};

void print_vector(t_vector v);


typedef	t_color	(*get_color)(t_object *obj);

t_color get_color_sphere(t_object *object);
t_color get_color_cylinder(t_object *object);
t_color get_color_plane(t_object *object);

static const get_color	g_get_color[] = {
	[SPHERE] = get_color_sphere,
	[CYLINDER] = get_color_cylinder,
	[PLANE] = get_color_plane
};
#endif