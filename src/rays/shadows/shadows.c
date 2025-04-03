#include "../../../inc/miniRT.h"

static t_intersec	*precompute_shadows(double *p, double *v, t_object **objs)
{
	double		*direction;
	t_ray		*ray;
	t_intersec	**i_s;

	direction = (double *)malloc(4 * sizeof(double));
	ft_memcpy(direction, v, 4 * sizeof(double));
	normalize(&direction);
	ray = create_ray(p, direction);
	i_s = get_intersections(ray, objs);
	return (identify_hit(i_s));
}

/* func to determine if a point belongs in the shadow or not
   takes a world and a point as parameters.
	objs are passed to match our get_intersections() implemenation

	The algorithm:
	1. 	measure the distance
	2. 	create a ray from point toward the light source by normalizing the vector from step 1
	3. 	intersect the world with that ray
	4. 	check if there's a hit
 */
bool	is_shadowed(t_world *w, double *p)
{
	t_intersec	*hit;
	double		*v;
	double		distance;

	v = subtract_tuple(w->light->coords, p);
	distance = magnitude(v);
	hit = precompute_shadows(p, v, w->objs);
	if (hit && hit->t < distance)
		return (true);
	return (false);
}
