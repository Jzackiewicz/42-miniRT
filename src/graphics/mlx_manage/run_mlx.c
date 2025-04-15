/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:15:56 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/15 13:30:00 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/graphics.h"
#include "../../../inc/miniRT.h"

static void	assign_textures(t_world *world, t_ray_tracer_data *rt_data)
{
	int	i;

	i = -1;
	while (world->objs[++i])
	{
		if (world->objs[i]->texture_path)
		{
			world->objs[i]->texture = create_image_texture(rt_data->mlx_data->mlx_ptr,
				world->objs[i]->texture, world->objs[i]->texture_path);
		}
	}
}

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
			&(*data)->mlx_data->bits_per_pixel, &(*data)->mlx_data->line_length,
			&(*data)->mlx_data->endian);
}

void	mlx_run(t_world *world_data, int no_lines, t_input_data **in_data)
{
	t_ray_tracer_data	*rt_data;
	int					**bitmap;

	rt_data = NULL;
	init_mlx(&rt_data);
	assign_textures(world_data, rt_data);
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
