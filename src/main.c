/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:02:41 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/13 13:47:58 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// TODO: properly analyze and test the intersection calculations
// norminette with ray management
// find out what to do next lol

int main()
{
	t_ray *ray;
	double o[] = {30.0, 0.0, 30.0, 1.0};
	double d[] = {1.0, 0.0, 0.0, 0.0};
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
	ray = create_ray(o, d);
	arr_t = intersect(objs[5], ray);
	free(ray);
	if (!arr_t)
	{
		free_objects(objs, no_objects);
		return (-1);
	}
	printf("t: %f, %f\n", arr_t[0], arr_t[1]);
	free(arr_t);
	free_objects(objs, no_objects);
}