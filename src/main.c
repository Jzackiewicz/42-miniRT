/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:02:41 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/12 15:40:39 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int main()
{
	t_ray ray;
	double o[] = {2.0, 2.0, 3.0, 1.0};
	double d[] = {1.0, 0.0, 0.0, 0.0};
	double	*pos;
	double	*arr_t;
	t_object	**objs;
	int			no_objects;
	
	objs = NULL;
	no_objects = parse_file("tests/integration_tests/testfiles/valid.rt",
			&objs);
	if (no_objects == -1)
	{
		printf("Error: file error\n");
		return (-1);
	}
	ray = *create_ray(o, d);
	pos = position(&ray, 2.33);
	arr_t = intersect(objs[3], &ray);
	if (!arr_t)
	{
		free_objects(objs, no_objects);
		return (-1);
	}
	//printf("point: {%f, %f, %f, %f}\n", pos[0], pos[1], pos[2], pos[3]);
	printf("t: %f, %f\n", arr_t[0], arr_t[1]);
	// free_objects(objs, no_objects);
	//printf("dir: {%f %f %f}, origin: {%f %f %f}", ray.direction[0], ray.direction[1], ray.direction[2], ray.origin[0], ray.origin[1], ray.origin[2]);
}