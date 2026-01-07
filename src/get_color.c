#include "miniRT.h"

t_color get_color_sphere(t_object *object)
{
    t_sphere    *sp;

    sp = (t_sphere *)object->object;
    return (sp->color);
}

t_color get_color_cylinder(t_object *object)
{
    t_cylinder    *c;

    c = (t_cylinder *)object->object;
    return (c->color);
}

t_color get_color_plane(t_object *object)
{
    t_plane   *p;

    p = (t_plane *)object->object;
    return (p->color);
}