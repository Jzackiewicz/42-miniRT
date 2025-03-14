/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:02:41 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/14 12:21:08 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// TODO: properly analyze and test the intersection calculations
// norminette with ray management
// find out what to do next lol

int	main(void)
{
	t_ray_tracer_data *rt_data;
	
	rt_data = NULL;
	init_mlx(&rt_data);
	render_image(rt_data);
	mlx_key_hook(rt_data->mlx_data->window_ptr, handle_key_input, rt_data);
	mlx_hook(rt_data->mlx_data->window_ptr, 17, 0, close_window, rt_data);
	mlx_loop(rt_data->mlx_data->mlx_ptr);
	clean_mlx(rt_data);
	return (0);
}

/* int main()
{
	t_ray ray;
	double o[] = {30.0, 0.0, 30.0, 1.0};
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
	// calcs the cylinder for now
	arr_t = intersect(objs[5], &ray);
	
	// practically means no intersection
	if (!arr_t)
	{
		free_objects(objs, no_objects);
		return (-1);
	}
	//printf("point: {%f, %f, %f, %f}\n", pos[0], pos[1], pos[2], pos[3]);
	printf("t: %f, %f\n", arr_t[0], arr_t[1]);
	// free_objects(objs, no_objects);
	//printf("dir: {%f %f %f}, origin: {%f %f %f}", ray.direction[0], ray.direction[1], ray.direction[2], ray.origin[0], ray.origin[1], ray.origin[2]);
} */