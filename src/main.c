/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:02:41 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/17 11:52:52 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int main()
{	
	// arbitraly chosen rays
	double o[] = {30.0, 0.0, 30.0, 1.0};
	double d[] = {1.0, 0.0, 0.0, 0.0};
	t_ray *ray;
	// t_ray	**cam_shot;
	t_ray_tracer_data *rt_data;
	t_input_data	**data;
	t_object		**objs;
	t_intersec	**ray_intersex;
	t_intersec	*hitpoint;
	// double		**bitmap;
	int			no_lines;
	
	data = NULL;
	rt_data = NULL;
	no_lines = parse_file("tests/integration_tests/testfiles/valid_nocy.rt",
			&data);
	if (no_lines == -1)
		return (printf("Error: file error\n"), -1);
	// objs extracted from the data_arr
	objs = get_objects(data, no_lines);
/* 	bitmap = init_bitmap(data);
	cam_shot = generate_rays(data);
	for (int i = 0; i < count_rays(cam_shot); i++)
	{
		ray_intersex[i] = get_sorted_intersections(ray, objs);	
		double *hitpoint = identify_hit(ray_intersex[i]);
	} */
	ray = create_ray(o, d);
	ray_intersex = get_sorted_intersections(ray, objs);	
	hitpoint = identify_hit(ray_intersex);
	clean_objects(objs, data, no_lines);
	clean_rays(ray_intersex, ray);
	init_mlx(&rt_data);
	//render_image(rt_data, hitpoint);
	// cleanups
	free(hitpoint);
	// mlx integration
	mlx_key_hook(rt_data->mlx_data->window_ptr, handle_key_input, rt_data);
	mlx_hook(rt_data->mlx_data->window_ptr, 17, 0, close_window, rt_data);
	mlx_loop(rt_data->mlx_data->mlx_ptr);
	clean_mlx(rt_data);
	return (0);
}
