/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/28 09:38:52 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(void)
{
	t_input_data	**data;
	t_object		**objs;
	t_camera		*cam_data;
	t_light			*light_data;
	t_ambient 		*ambient;
	int				**bitmap;
	int				no_lines;

	data = NULL;
	no_lines = parse_file("tests/integration_tests/testfiles/valid_nocy.rt",
			&data);
	if (no_lines == -1)
		return (printf("Error: file error\n"), -1);
	objs = get_objects(data, no_lines);
	cam_data = get_cam_data(data, no_lines);
	light_data = get_light_data(data, no_lines);
	ambient = get_ambient_data(data, no_lines);
	for (int i = 0; i < no_lines - 3; i++)
		assign_object_material(ambient, objs[i]);
	ray_for_pixel(cam_data, 0, 0);
	//bitmap = generate_bitmap(cam_data, objs, light_data, ambient);
	free_objects(data, objs, no_lines);
	free(cam_data);
	// mlx_run(bitmap);
	return (0);
}
