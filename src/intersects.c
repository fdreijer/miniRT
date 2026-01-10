#include "miniRT.h"

void    ray_obstructed(t_scene *scene, t_vector point, t_object *this, t_intersection *intersection)
{
    t_object        *obj;
    t_ray           light_ray;
    t_intersection  light_intersection;
    t_vector        light_dir;

    light_dir = v_sub(scene->light.pos, point);
    obj = scene->all_objects;
    light_ray.origin = point;
    light_ray.dir = v_normalize(v_sub(scene->light.pos, point));
    while (obj)
    {
        light_intersection.angle = 1;
        if (this != obj && g_intersects[obj->type](scene, light_ray, obj, \
&light_intersection) && light_intersection.distance < sqrt(v_dot(light_dir, light_dir)))
        {
            intersection->angle = 0;
            return ;
        }
        obj = obj->next;
    }
}

void  angle_sphere(t_scene *scene, t_ray ray, t_object *this, t_intersection *intersection)
{
    t_sphere *sp;
    t_vector intersect_point;
    t_vector normal;
    t_vector light_dir;

    sp = (t_sphere *)this->object;
    intersect_point = v_add(ray.origin, v_scale(ray.dir, intersection->distance));
    normal = v_normalize(v_sub(intersect_point, sp->pos));
    light_dir = v_normalize(v_sub(scene->light.pos, intersect_point));
    intersection->angle = v_dot(normal, light_dir);
    if (intersection->angle < 0)
        intersection->angle = 0;
    ray_obstructed(scene, intersect_point, this, intersection);
}

int intersects_sphere(t_scene *scene, t_ray ray, t_object *this, t_intersection *intersection){
    t_sphere    *sp;
    t_vector    oc;
    double      b;
    double      c;
    double      discriminant;

    sp = (t_sphere *)this->object;
    oc = v_sub(ray.origin, sp->pos);
    b = 2 * v_dot(oc, ray.dir);
    c = v_dot(oc, oc) - ((sp->diameter / 2.0f) * (sp->diameter / 2.0f));
    discriminant = b * b - 4.0 * c;
    if (((-b + sqrt(discriminant)) / 2.0f) > 0 && ((-b - sqrt(discriminant)) / 2.0f) > 0)
        intersection->distance = fmin(-b + sqrt(discriminant)\
/ 2.0f, (-b - sqrt(discriminant)) / 2.0f);
    else
        intersection->distance = fmax(-b + sqrt(discriminant)\
/ 2.0f, (-b - sqrt(discriminant)) / 2.0f);
    if (intersection->distance <= 0)
        return (0);
    if (!intersection->angle)
        angle_sphere(scene, ray, this, intersection);
    return (1);
}


void    angle_plane(t_scene *scene, t_ray ray, t_object *this, t_intersection *intersection)
{
    t_plane     *pl;
    t_vector    intersect_point;
    t_vector    normal;
    t_vector    light_dir;
    double      dot_normal_ray;

    pl = (t_plane *)this->object;
    intersect_point = v_add(ray.origin, v_scale(ray.dir, intersection->distance));
    light_dir = v_normalize(v_sub(scene->light.pos, intersect_point));
    dot_normal_ray = v_dot(pl->normal, ray.dir);
    if (dot_normal_ray > 0)
        normal = v_scale(pl->normal, -1.0);
    else
        normal = pl->normal;
    intersection->angle = v_dot(normal, light_dir);
    if (intersection->angle < 0)
        intersection->angle = 0;
    ray_obstructed(scene, intersect_point, this, intersection);
}

int intersects_plane(t_scene *scene, t_ray ray, t_object *this, t_intersection *intersection){
    t_plane *p;

    p = (t_plane *)this->object;
    intersection->distance = -v_dot(v_sub(ray.origin, p->pos), p->normal) / v_dot(ray.dir, p->normal);
    if (intersection->distance <= 0)
        return (0);
    if (!intersection->angle)
        angle_plane(scene, ray, this, intersection);
    return (1);
}

