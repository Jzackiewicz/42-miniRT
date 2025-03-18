/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:02:41 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/18 10:29:08 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// generate rays on canvas with color
// create a func to generate a bitmap, with ones 

int main()
{	
	// arbitraly chosen rays
	// double o[] = {30.0, 0.0, 30.0, 1.0};
	// double d[] = {1.0, 0.0, 0.0, 0.0};
	t_ray *ray;
	t_ray_tracer_data *rt_data;
	t_input_data	**data;
	t_object		**objs;
	t_intersec	***ray_intersex;
	t_intersec	*hitpoint;
	int		**bitmap;
	int			no_lines;
	
	data = NULL;
	rt_data = NULL;
	no_lines = parse_file("tests/integration_tests/testfiles/valid_nocy.rt",
			&data);
	if (no_lines == -1)
		return (printf("Error: file error\n"), -1);
	// objs extracted from the data_arr
	objs = get_objects(data, no_lines);
	t_camera *cam_data = get_cam_data(data, no_lines);
	t_ray	**cam_shot = generate_rays(cam_data);
	ray_intersex = find_all_intersections(cam_shot, objs);
	bitmap = generate_bitmap(ray_intersex, cam_shot, cam_data);
	init_mlx(&rt_data);
	render_image(rt_data, bitmap);
	// cleanups
	mlx_key_hook(rt_data->mlx_data->window_ptr, handle_key_input, rt_data);
	mlx_hook(rt_data->mlx_data->window_ptr, 17, 0, close_window, rt_data);
	mlx_loop(rt_data->mlx_data->mlx_ptr);
	clean_mlx(rt_data);
	return (0);
}
