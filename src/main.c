/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:02:41 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/18 12:52:59 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	free_bitmap(int **bitmap)
{
	int	i;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		free(bitmap[i]);
		i++;
	}
	free(bitmap);
}

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
	objs = get_objects(data, no_lines);
	cam_data = get_cam_data(data, no_lines);
	cam_shot = generate_rays(cam_data);
	ray_intersex = find_all_intersections(cam_shot, objs);
	bitmap = generate_bitmap(ray_intersex, cam_shot, cam_data);
	free(cam_data);
	free_bitmap(bitmap);
	(void) bitmap;
	// mlx_run(bitmap);
	clean_rays(cam_shot);
	clean_intersections(ray_intersex);
	free_objects(data, no_lines);
	for (int i = 0; objs[i]; i++)
		free(objs[i]);
	free(objs);
	return (0);
}
