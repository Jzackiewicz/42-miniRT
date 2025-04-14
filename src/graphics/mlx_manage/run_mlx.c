/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:15:56 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/14 17:32:48 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/graphics.h"
#include "../../../inc/miniRT.h"

static void	init_mlx(t_ray_tracer_data **data)
{
	*data = malloc(sizeof(t_ray_tracer_data));
	if (!(*data))
		exit(1);
	(*data)->mlx_data = malloc(sizeof(t_mlx_data));
	if (!(*data)->mlx_data)
		exit(1);
	(*data)->mlx_data->mlx_ptr = mlx_init();
	(*data)->mlx_data->window_ptr = mlx_new_window((*data)->mlx_data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT");
	(*data)->mlx_data->img_ptr = mlx_new_image((*data)->mlx_data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	(*data)->mlx_data->img_addr = mlx_get_data_addr((*data)->mlx_data->img_ptr,
			&(*data)->mlx_data->bits_per_pixel,
			&(*data)->mlx_data->line_length, &(*data)->mlx_data->endian);
}

void	mlx_run(t_world *world_data, int no_lines, t_input_data **in_data)
{
	t_ray_tracer_data	*rt_data;
	int **bitmap;
	
	rt_data = NULL;
	init_mlx(&rt_data);
	for (int i = 0; world_data->objs[i]; i++)
	{
		if (0 == ft_strncmp(world_data->objs[i]->id, "sp\0", 3))
		{
			t_object *obj = world_data->objs[i];
			ft_memset(&(obj->texture), 0, sizeof(t_texture));
			create_image_texture(rt_data->mlx_data->mlx_ptr, &(obj->texture), "textures/earth_day.xpm");
		}
	}
	bitmap = generate_bitmap(world_data);
	if (bitmap)
		render_image(rt_data, bitmap);
	free_input_data(in_data, no_lines);
	free_world(world_data);
	mlx_key_hook(rt_data->mlx_data->window_ptr, handle_key_input, rt_data);
	mlx_hook(rt_data->mlx_data->window_ptr, 17, 0, close_window, rt_data);
	if (bitmap)
		free_bitmap(bitmap);
	mlx_loop(rt_data->mlx_data->mlx_ptr);
}
