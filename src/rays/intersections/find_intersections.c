/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:34:26 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/18 09:27:07 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/rays.h"
#include "../../../inc/miniRT.h"

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

	denom = dot(ray->direction, obj->orientation_vector);
	if (compare_floats(denom, 0.0))
		return (NULL);
	sub = subtract_tuple(obj->coords, ray->origin);
	t = dot(obj->orientation_vector, sub) / denom;
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

t_intersec ***find_all_intersections(t_ray **rays, t_object **objs)
{
    int i = 0;
    int ray_count = 0;
    t_intersec ***res;
	
    while (rays[ray_count])
        ray_count++;
    res = (t_intersec ***)malloc(sizeof(t_intersec**) * (ray_count + 1));
    if (!res)
        return NULL;
    
    i = 0;
    while (rays[i])
    {
        res[i] = get_sorted_intersections(rays[i], objs);
        i++;
    }
    res[i] = NULL;
    
    return res;
}
