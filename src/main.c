/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:11:15 by kali              #+#    #+#             */
/*   Updated: 2025/10/05 16:55:41 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void print_vector(t_vector v)
{
    printf("%.2f,%.2f,%.2f", v.x, v.y, v.z);
}

void print_color(t_color c)
{
    printf("%d,%d,%d", c.r, c.g, c.b);
}

void print_ambient(t_ambient *a)
{
    printf("#AMBIENT LIGHT\tLIGHTING RATIO\tCOLOR\n");
    printf("A\t\t%.2f\t\t", a->ratio);
    print_color(a->color);
    printf("\n\n");
}

void print_camera(t_camera *c)
{
    printf("#CAMERA\tCOORDINATES\tORIENTATION\tFOV\n");
    printf("C\t\t");
    print_vector(c->pos);
    printf("\t");
    print_vector(c->normal);
    printf("\t%.0f\n\n", c->fov);
}

void print_lights(t_light *head)
{
    printf("#LIGHT\tCOORDINATES\tBRIGHTNESS\tCOLOR\n");
    while (head)
    {
        printf("L\t\t");
        print_vector(head->pos);
        printf("\t%.2f\t\t", head->brightness);
        print_color(head->color);
        printf("\n");
        head = head->next;
    }
    printf("\n");
}

void print_planes(t_plane *head)
{
    printf("#PLANE\tCOORDINATES\tNORMAL\tCOLOR\n");
    while (head)
    {
        printf("pl\t\t");
        print_vector(head->pos);
        printf("\t");
        print_vector(head->normal);
        printf("\t");
        print_color(head->material->diffuse);
        printf("\n");
        head = head->next;
    }
    printf("\n");
}

void print_spheres(t_scene *scene)
{
    t_object *obj = scene->all_objects;

    printf("#SPHERE\tCOORDINATES\tDIAMETER\tCOLOR\n");
    while (obj)
    {
        if (obj->type == SPHERE)
        {
            t_sphere *sp = (t_sphere *)obj->object;
            printf("sp\t\t");
            print_vector(sp->pos);
            printf("\t%.2f\t\t", sp->diameter);
            print_color(sp->material->diffuse);
            printf("\n");
        }
        obj = obj->next;
    }
    printf("\n");
}

void print_cylinders(t_scene *scene)
{
    t_object *obj = scene->all_objects;

    printf("#CYLINDER\tCOORDINATES\tDIRECTION\tHEIGHT\tWIDTH\tCOLOR\n");
    while (obj)
    {
        if (obj->type == CYLINDER)
        {
            t_cylinder *c = (t_cylinder *)obj->object;
            printf("cy\t\t");
            print_vector(c->pos);
            printf("\t");
            print_vector(c->normal);
            printf("\t%.2f\t%.2f\t", c->height, c->diameter);
            print_color(c->material->diffuse);
            printf("\n");
        }
        obj = obj->next;
    }
    printf("\n");
}

void print_scene(t_scene *scene)
{
    print_ambient(&scene->ambient);
    print_camera(&scene->cam);
    print_lights(scene->lights);
    print_planes(scene->grid.planes);
    print_spheres(scene);
    print_cylinders(scene);
}


int main(void)
{
	char	*scene_file = "scenes/scene.rt";
	t_scene	*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (1);
	parse_file(scene, scene_file);
	print_scene(scene);
}