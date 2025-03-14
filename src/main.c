/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:02:41 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/14 15:38:41 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

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

int main()
{	
	// arbitraly chosen rays
	double o[] = {30.0, 0.0, 30.0, 1.0};
	double d[] = {1.0, 0.0, 0.0, 0.0};
	t_ray *ray;
	t_ray_tracer_data *rt_data;
	t_input_data	**data;
	t_object		**objs;
	t_intersec	**ray_intersex;
	int			no_lines;
	
	// objs & settings arr
	data = NULL;
	rt_data = NULL;
	no_lines = parse_file("tests/integration_tests/testfiles/valid_nocy.rt",
			&data);
	// objs extracted from the data_arr
	objs = get_objects(data, no_lines);
	if (no_lines == -1)
	{
		printf("Error: file error\n");
		return (-1);
	}
	// ray creation
	ray = create_ray(o, d);
	// ray intersection array
	ray_intersex = (t_intersec **) ft_calloc(((no_lines - 3) * 2 + 1), sizeof(t_intersec *));
	if (!ray_intersex)
		return (-1);
		
	// intersection calculation
	calc_intersections(ray, objs, ray_intersex);
	sort_intersections(ray_intersex, 0, ((no_lines - 3) * 2 - 1));
	
	// mlx integration
	init_mlx(&rt_data);
	double *hitpoint = calc_hit_point(ray, ray_intersex);
	render_image(rt_data, hitpoint);
	free(hitpoint);
	mlx_key_hook(rt_data->mlx_data->window_ptr, handle_key_input, rt_data);
	mlx_hook(rt_data->mlx_data->window_ptr, 17, 0, close_window, rt_data);
	mlx_loop(rt_data->mlx_data->mlx_ptr);
	
	// cleanups
	clean_mlx(rt_data);
	clean_rays(ray_intersex, ray);
	clean_objects(objs, data, no_lines);
	return (0);
}