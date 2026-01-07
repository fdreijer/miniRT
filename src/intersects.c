#include "miniRT.h"

void  angle_sphere(t_scene *scene, t_ray ray, t_sphere *sp, t_intersection *intersection)
{
    t_vector intersect_point = v_add(ray.origin, v_scale(ray.dir, intersection->distance));
    t_vector normal = v_normalize(v_sub(intersect_point, sp->pos));
    t_vector reflected_ray = v_sub(v_scale(normal, 2 * v_dot(ray.dir, normal)), ray.dir);
    t_vector light_dir = v_normalize(v_sub(scene->light.pos, intersect_point));
    intersection->angle = v_dot(reflected_ray, light_dir);
    if (intersection->angle < 0)
        intersection->angle = 0;
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
    intersection->distance = ft_dmax((-b + sqrt(discriminant))\
/ 2.0f, (-b - sqrt(discriminant)) / 2.0f);
    if (intersection->distance <= 0)
        return (0);
    angle_sphere(scene, ray, sp, intersection);
    return (1);
}
