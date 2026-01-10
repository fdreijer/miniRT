#include "miniRT.h"

t_ray generate_ray(t_scene *scene, int x, int y) {
    t_ray   ray;
    float   horizontal;
    float   vertical;

    horizontal = (2.0 * x / WIDTH - 1.0) * ASPECT_RATIO;
    vertical = (1.0 - 2.0 * y / HEIGHT);
    ray.origin = scene->cam.pos;
    ray.dir = v_normalize(v_add(v_add(scene->cam.normal, \
v_scale(scene->cam.right, horizontal * scene->cam.tan_half_fov)), \
v_scale(scene->cam.up, vertical * scene->cam.tan_half_fov)));

    return ray;
}
t_color scale_color(t_scene *scene, t_color color, double angle)
{
    t_color final_color;

    final_color.r = fmin(255.0, ((color.r / 255.0) * \
((scene->ambient.color.r / 255.0) * scene->ambient.ratio + \
(scene->light.color.r / 255.0) * angle * scene->light.brightness)) * 255.0);
    final_color.g = fmin(255.0, ((color.g / 255.0) * \
((scene->ambient.color.g / 255.0) * scene->ambient.ratio + \
(scene->light.color.g / 255.0) * angle * scene->light.brightness)) * 255.0);
    final_color.b = fmin(255.0, ((color.b / 255.0) * \
((scene->ambient.color.b / 255.0) * scene->ambient.ratio + \
(scene->light.color.b / 255.0) * angle * scene->light.brightness)) * 255.0);
    return final_color;
}

t_color trace_ray(t_scene *scene, t_ray ray)
{
    t_color         color;
    t_object        *obj;
    t_intersection  intersection;
    double          distance;

    color = (t_color){0, 0, 0};
    obj = scene->all_objects;
    distance = INFINITY;
    while (obj)
    {
        intersection.angle = 0;
        if (g_intersects[obj->type](scene, ray, obj, &intersection) && intersection.distance < distance)
        {
            distance = intersection.distance;
            // printf("%d\n", g_get_color[obj->type](obj).b);
            color = scale_color(scene, g_get_color[obj->type](obj), intersection.angle);
        }
        obj = obj->next;
    }
    return (color);
}

int generate_rays(t_scene *scene)
{
    int     x;
    int     y;
    t_ray   ray;
    t_color color;

    x = -1;
    while (++x < WIDTH)
    {
        y = -1;
        while (++y < HEIGHT)
        {
            ray = generate_ray(scene, x, y);
            color = trace_ray(scene, ray);
            mlx_put_pixel(scene->image, x, y, \
(uint32_t)((color.r << 24) | (color.g << 16) | (color.b << 8) | 0xFF));
        }
    }
    return (0);
}