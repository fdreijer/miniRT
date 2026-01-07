#include "miniRT.h"

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

typedef struct s_bounding_tree
{
	t_object				*object;
	struct s_bounding_tree	*left;
	struct s_bounding_tree	*right;
	t_vector		min_bounds;
	t_vector		max_bounds;
}							t_bounding_tree;

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

void	calculate_bounds_sphere(t_object *object, t_sphere *s)
{
	double	r;

	r = s->diameter / 2;
	// object->min_bounds = (t_vector){s->pos.x - r, s->pos.y - r, s->pos.z - r};
	// object->max_bounds = (t_vector){s->pos.x + r, s->pos.y + r, s->pos.z + r};
}

void	calculate_bounds_cylinder(t_object *object, t_cylinder *c)
{
	double		r;
	t_vector	b;
	t_vector	t;

	r = c->diameter / 2;
	b = v_sub(c->pos, v_scale(c->normal, c->height / 2.0));
	t = v_add(c->pos, v_scale(c->normal, c->height / 2.0));
// 	object->min_bounds = (t_vector){fmin(b.x, t.x) - r, fmin(b.y, t.y) - \
// r, fmin(b.z, t.z) - r};
// 	object->max_bounds = (t_vector){fmax(b.x, t.x) + r, fmax(b.y, t.y) + \
r, fmax(b.z, t.z) + r};
}

void	calculate_bounds_obj(t_object *object, void *obj, t_type type)
{
	if (type == SPHERE)
		calculate_bounds_sphere(object, (t_sphere *)obj);
	else if (type == CYLINDER)
		calculate_bounds_cylinder(object, (t_cylinder *)obj);
}

t_color	scale_color(t_color c, double s)
{
	return ((t_color){fmin(c.r * s, 255), fmin(c.g * s, 255), \
fmin(c.b * s, 255)});
}

t_material	*make_material(t_color color)
{
	t_material	*m;

	m = ft_calloc(1, sizeof(t_material));
	if (!m)
		return (NULL);
	m->ambient = scale_color(color, 0.2);
	m->diffuse = scale_color(color, 0.7);
	m->specular = scale_color((t_color){255, 255, 255}, 0.1);
	m->shine = 32.0;
	m->reflectivity = 0.0;
	m->texture = NONE;
	return (m);
}