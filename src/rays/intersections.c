/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:34:26 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/14 16:52:27 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"
#include "../../inc/miniRT.h"

double	*intersect_sphere(t_object *obj, t_ray *ray)
{
	double	*arr_t;
	double	*oc_vector;
	double	b;
	double	c;
	double	delta;

	oc_vector = subtract_tuple(ray->origin, obj->coords);
	b = dot(oc_vector, ray->direction) * 2;
	c = dot(oc_vector, oc_vector) - pow(obj->diameter / 2, 2);
	free(oc_vector);
	delta = pow(b, 2) - 4 * c;
	if (delta < 0)
		return (NULL);
	arr_t = (double *)malloc(sizeof(double) * 2);
	if (!arr_t)
		return (NULL);
	arr_t[0] = (-b + sqrt(delta)) / 2;
	arr_t[1] = (-b - sqrt(delta)) / 2;
	return (arr_t);
}

double	*intersect_plane(t_object *obj, t_ray *ray)
{
	double	*arr_t;
	double	denom;
	double	t;
	double	*sub;

	denom = dot(ray->direction, obj->normal_vector);
	if (compare_floats(denom, 0.0))
		return (NULL);
	sub = subtract_tuple(obj->coords, ray->origin);
	t = dot(obj->normal_vector, sub) / denom;
	free(sub);
	arr_t = (double *)malloc(sizeof(double) * 2);
	if (!arr_t)
		return (NULL);
	arr_t[0] = t;
	arr_t[1] = t;
	return (arr_t);
}

/* highest level intersection finding function
	called with a pointer to an object (plane, sphere or cylinder)
	and an initialized t_ray pointer */
double	*intersect(t_object *obj, t_ray *ray)
{
	double	*arr_t;

	arr_t = NULL;
	if (!ft_strncmp(obj->id, "sp\0", 3))
		arr_t = intersect_sphere(obj, ray);
	else if (!ft_strncmp(obj->id, "pl\0", 3))
		arr_t = intersect_plane(obj, ray);
	else
	{
		printf("Error: unknown object id: %s\n", obj->id);
		return (NULL);
	}
	return (arr_t);
}

void append_intersec(t_intersec **all, double *arr_t, t_object *obj, int intersec_no)
{
    t_intersec *x;
    int i;
    int position;

    if (!all || !obj || !arr_t)
        return;
    
    i = 0;
    while (i < 2)
    {
        position = (intersec_no * 2) + i;
        x = (t_intersec *)malloc(sizeof(t_intersec));
        if (!x)
            return;
        x->t = arr_t[i];
        x->object = obj;
        all[position] = x;
        i++;
    }
    all[(intersec_no * 2) + 2] = NULL;
}

void calc_intersections(t_ray *ray, t_object **objs, t_intersec **ray_intersex)
{
	int i;
	double *arr_t;

	i = 0;
	while (objs[i])
	{
		arr_t = intersect(objs[i], ray);
		if (arr_t)
		{
			append_intersec(ray_intersex, arr_t, objs[i], i);
			free(arr_t);
		}
		i++;
	}
}
