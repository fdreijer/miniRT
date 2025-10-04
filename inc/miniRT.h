/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:46:57 by kali              #+#    #+#             */
/*   Updated: 2025/10/04 18:46:34 by kali             ###   ########.fr       */
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
	float	x;
	float	y;
	float	z;
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
	t_vector	dir;
	float		fov;
}				t_camera;

typedef struct s_ambient
{
	float	ratio;
	t_color	color;
}			t_ambient;

typedef struct s_light
{
	t_vector		pos;
	float			brightness;
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
	float		shine;
	float		reflectivity;
	t_texture	texture;
	void		*texture_data;
}				t_material;

typedef struct s_sphere
{
	t_vector	pos;
	float		diameter;
	t_material	*material;
}				t_sphere;

typedef struct s_plane
{
	t_vector	pos;
	t_vector	normal;
	t_material	*material;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	pos;
	t_vector	normal;
	float		diameter;
	float		height;
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
	t_type		type;
	void		*object;
	t_vector	min_bounds;
	t_vector	max_bounds;
}				t_object;

typedef struct s_list
{
	t_object		*object;
	struct s_list	*next;
}					t_list;

typedef struct s_voxel
{
	t_list			*objects;
	t_vector		min_bounds;
	t_vector		max_bounds;
}					t_voxel;

typedef struct s_grid
{
	t_voxel			***voxels;
	t_vector		min_bounds;
	t_vector		max_bounds;
	float			cell_size;
}					t_grid;

typedef struct s_scene
{
	t_camera	cam;
	t_ambient	ambient;
	t_light		*lights;
	t_grid		grid;
}				t_scene;

#endif