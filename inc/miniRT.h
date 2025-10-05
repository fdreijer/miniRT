/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:46:57 by kali              #+#    #+#             */
/*   Updated: 2025/10/05 16:55:31 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define VOXEL_GRID_SIZE 10

# include "libft/inc/libft.h"

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>

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
	struct s_light	*next;
}				t_light;

typedef enum e_texture
{
	NONE,
	CHECKERED,
	BUMP_MAP
}	t_texture;

typedef struct s_material
{
	t_color		ambient;
	t_color 	diffuse;
	t_color 	specular;
	double		shine;
	double		reflectivity;
	t_texture	texture;
	void		*texture_data;
}				t_material;

typedef struct s_sphere
{
	t_vector	pos;
	double		diameter;
	t_material	*material;
}				t_sphere;

typedef struct s_plane
{
	t_vector		pos;
	t_vector		normal;
	t_material		*material;
	struct s_plane		*next;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	pos;
	t_vector	normal;
	double		diameter;
	double		height;
	t_material	*material;
}				t_cylinder;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef struct s_object
{
	t_type			type;
	void			*object;
	t_vector		min_bounds;
	t_vector		max_bounds;
	struct s_object	*next;
}				t_object;

typedef struct s_voxel
{
	t_object		*objects;
	t_vector		min_bounds;
	t_vector		max_bounds;
}					t_voxel;

typedef struct s_grid
{
	t_voxel			***voxels;
	t_plane			*planes;
	t_vector		min_bounds;
	t_vector		max_bounds;
	double			cell_size;
}					t_grid;

typedef struct s_scene
{
	t_camera	cam;
	t_ambient	ambient;
	t_light		*lights;
	t_grid		grid;
	t_object	*all_objects;
}				t_scene;

void		parse_file(t_scene *scene, char *scene_file);
t_vector	v_add(t_vector v1, t_vector v2);
t_vector	v_sub(t_vector v1, t_vector v2);
t_vector	v_scale(t_vector v, double s);
int			v_in_bounds(t_vector v, double min, double max);

#endif