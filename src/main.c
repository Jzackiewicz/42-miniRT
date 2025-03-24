/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/24 13:19:10 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/miniRT.h"

int	main(void)
{
	t_input_data	**data;
	t_object		**objs;
	t_intersec		***ray_intersex;
	int				**bitmap;
	int				no_lines;
	t_camera		*cam_data;
	t_ray			**cam_shot;

	data = NULL;
	no_lines = parse_file("tests/integration_tests/testfiles/valid_nocy.rt",
			&data);
	if (no_lines == -1)
		return (printf("Error: file error\n"), -1);
	
	cam_data = get_cam_data(data, no_lines);
	objs = get_objects(data, no_lines);
	bitmap = generate_new_bitmap(cam_data, objs);
	
	// t_ambient *ambient = get_ambient_data(data, no_lines);
	// for (int i = 0; i < no_lines - 3; i++)
	// {
	// 	assign_object_material(ambient, objs[i]);
	// }
	// 
	// cam_shot = generate_rays(cam_data);
	// ray_intersex = find_all_intersections(cam_shot, objs);
	// bitmap = generate_bitmap(ray_intersex, cam_shot, cam_data, get_light_data(data, no_lines));
	// clean_rays(cam_shot);
	// clean_intersections(ray_intersex);
	// free_objects(data, objs, no_lines);
	// free(cam_data);
	mlx_run(bitmap);
	return (0);
}
