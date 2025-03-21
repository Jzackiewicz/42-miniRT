/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:26:53 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/21 13:03:43 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/rays.h"
#include "../../../inc/miniRT.h"

int	count_intersections(t_intersec **intersex)
{
	int	count;

	count = 0;
	while (intersex[count])
		count++;
	return (count);
}

static void	append_intersec(t_intersec **all, double *arr_t, t_object *obj, int intersec_no)
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

static t_intersec	**get_intersections(t_ray *ray, t_object **objs)
{
	int i;
	double *arr_t;
	t_intersec	**intersex;

	if (!ray || !objs || !*objs)
		return (NULL);
	intersex = (t_intersec **)ft_calloc(count_objects(objs) * 2 + 1, sizeof(t_intersec *));
	if (!intersex)
		return (NULL);
	i = 0;
	while (objs[i])
	{
		ray = ray_to_object_space(ray, objs[i]);
		arr_t = intersect(objs[i], ray);
		if (arr_t)
		{
			append_intersec(intersex, arr_t, objs[i], i);
			free(arr_t);
		}
		i++;
	}
	return (intersex);
}

t_intersec **get_sorted_intersections(t_ray	*ray, t_object **objs)
{
	t_intersec	**intersex;

	intersex = get_intersections(ray, objs);
	if (!intersex)
		return (NULL);
	sort_intersections(intersex, 0, count_intersections(intersex) - 1);
	return (intersex);
}

// i_s: intersections array sorted in ascending order
// returns NULL on non-negative t not found
t_intersec	*identify_hit(t_intersec **i_s)
{
	int i = 0;
	
	if (!i_s)
		return (NULL);
	while (i_s[i])
	{
		if (i_s[i]->t > 0)
			return (i_s[i]);
		i++;
	}
	return (NULL);
}
