/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:02:41 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/13 17:35:05 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// TODO:	properly analyze and test the intersection calculations
//			differenct struct for objects and settings

int main()
{
	t_ray *ray;
	double o[] = {30.0, 0.0, 30.0, 1.0};
	double d[] = {1.0, 0.0, 0.0, 0.0};
	double	*arr_t;
	t_object	**objs;
	t_intersec	*ray_intersex;
	int			no_objects;
	
	objs = NULL;
	no_objects = parse_file("tests/integration_tests/testfiles/valid_nocy.rt",
			&objs);
	if (no_objects == -1)
	{
		printf("Error: file error\n");
		return (-1);
	}
	ray = create_ray(o, d);
	ray_intersex = (t_intersec *)ft_calloc(no_objects + 1, sizeof(t_intersec));
	if (!ray_intersex)
		return (-1);
	for (int i = 0; i < no_objects; i++)
	{
		if (!ft_strncmp(objs[i]->id, "A\0", 2) || !ft_strncmp(objs[i]->id, "C\0", 2) || !ft_strncmp(objs[i]->id, "L\0", 2))
			continue ; 
		arr_t = intersect(objs[i], ray);
		append_intersec(&ray_intersex, arr_t, objs[i], i);
		//free(arr_t);
	}
	
	for (int i = 0; i < no_objects; i++)
	{
		printf("main: %f\n", ray_intersex[i].t);
	}
	free(ray);
	free_objects(objs, no_objects);
	if (!arr_t)
		return (-1);
}