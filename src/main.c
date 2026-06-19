/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:34:28 by fdreijer          #+#    #+#             */
/*   Updated: 2026/06/19 15:09:54 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// void print_vector(t_vector v)
// {
// 	printf("%.2f,%.2f,%.2f", v.x, v.y, v.z);
// }

// void print_color(t_color c)
// {
// 	printf("%d,%d,%d", c.r, c.g, c.b);
// }

// void print_ambient(t_ambient *a)
// {
// 	printf("#AMBIENT LIGHT\tLIGHTING RATIO\tCOLOR\n");
// 	printf("A\t\t%.2f\t\t", a->ratio);
// 	print_color(a->color);
// 	printf("\n\n");
// }

// void print_camera(t_camera *c)
// {
// 	printf("#CAMERA\tCOORDINATES\tORIENTATION\tFOV\n");
// 	printf("C\t\t");
// 	print_vector(c->pos);
// 	printf("\t");
// 	print_vector(c->normal);
// 	printf("\t%.0f\n\n", c->fov);
// }

// void print_light(t_light *l)
// {
// 	printf("#LIGHT\tCOORDINATES\tBRIGHTNESS\tCOLOR\n");
// 	printf("L\t\t");
// 	print_vector(l->pos);
// 	printf("\t%.2f\t\t", l->brightness);
// 	print_color(l->color);
// 	printf("\n\n");
// }

// void print_planes(t_scene *scene)
// {
// 	t_object *obj = scene->all_objects;

// 	printf("#PLANE\tCOORDINATES\tNORMAL\tCOLOR\n");
// 	while (obj)
// 	{
// 		if (obj->type == PLANE)
// 		{
// 			t_plane *p = (t_plane *)obj->object;
// 			printf("pl\t\t");
// 			print_vector(p->pos);
// 			printf("\t");
// 			print_vector(p->normal);
// 			printf("\t");
// 			print_color(p->color); // Changed from material->diffuse to color
// 			printf("\n");
// 		}
// 		obj = obj->next;
// 	}
// 	printf("\n");
// }

// void print_spheres(t_scene *scene)
// {
// 	t_object *obj = scene->all_objects;

// 	printf("#SPHERE\tCOORDINATES\tDIAMETER\tCOLOR\n");
// 	while (obj)
// 	{
// 		if (obj->type == SPHERE)
// 		{
// 			t_sphere *sp = (t_sphere *)obj->object;
// 			printf("sp\t\t");
// 			print_vector(sp->pos);
// 			printf("\t%.2f\t\t", sp->diameter);
// 			print_color(sp->color);  // Changed from material->diffuse to color
// 			printf("\n");
// 		}
// 		obj = obj->next;
// 	}
// 	printf("\n");
// }

// void print_cylinders(t_scene *scene)
// {
// 	t_object *obj = scene->all_objects;

// 	printf("#CYLINDER\tCOORDINATES\tDIRECTION\tHEIGHT\tWIDTH\tCOLOR\n");
// 	while (obj)
// 	{
// 		if (obj->type == CYLINDER)
// 		{
// 			t_cylinder *c = (t_cylinder *)obj->object;
// 			printf("cy\t\t");
// 			print_vector(c->pos);
// 			printf("\t");
// 			print_vector(c->normal);
// 			printf("\t%.2f\t%.2f\t", c->height, c->diameter);
// 			print_color(c->color); // Changed from material->diffuse to color
// 			printf("\n");
// 		}
// 		obj = obj->next;
// 	}
// 	printf("\n");
// }

// void print_scene(t_scene *scene)
// {
// 	print_ambient(&scene->ambient);
// 	print_camera(&scene->cam);
// 	print_light(&scene->light);  // Print the single light
// 	print_spheres(scene);
// 	print_cylinders(scene);
// 	print_planes(scene);
// }

#include <sys/time.h>

static double	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
}

void	key_down(t_scene *scene)
{
	if (mlx_is_key_down(scene->mlx, MLX_KEY_UP))
		scene->cam.pos.x += 1;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_DOWN))
		scene->cam.pos.x -= 1;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT))
		scene->cam.pos.y += 1;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT))
		scene->cam.pos.y -= 1;
}

void	ft_hook(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	key_down(scene);
	double t = now_ms();
	generate_rays(scene);
	fprintf(stderr, "frame time: %.1f ms\n", now_ms() - t);
}

int	str_ends_with(char *s1, char *s2)
{
	int	len1;
	int	len2;
	int	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 < len2)
		return (0);
	i = len2;
	while (i)
	{
		if (s1[len1 - len2 + i - 1] != s2[i - 1])
			return (0);
		i--;
	}
	return (1);
}

int validate_args(int argc, char **argv, char **scene_file){
	if (argc != 2 || !argv || !argv[1] || !str_ends_with(argv[1], ".rt"))
		return (0);
	*scene_file = argv[1];
	return (1);
}

int	main(int argc, char **argv)
{
	char	*scene_file;
	t_scene	*scene = {0};

	if (!validate_args(argc, argv, &scene_file))
		return (write(2, "Invalid file\n", 13), 1);
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (1);
	double t = now_ms();
	if (!parse_file(scene, scene_file))
		free_scene_exit(scene, "invalid scene\n", 1);
	fprintf(stderr, "parse: %.1f ms\n", now_ms() - t); t = now_ms();
	scene->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	scene->image = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	fprintf(stderr, "mlx init: %.1f ms\n", now_ms() - t); t = now_ms();
	//t = now_ms();
	//generate_rays(scene);
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	//fprintf(stderr, "first render: %.1f ms\n", now_ms() - t);
	// print_scene(scene);
	mlx_loop_hook(scene->mlx, ft_hook, scene);
	printf("a");
	mlx_loop(scene->mlx);
}
