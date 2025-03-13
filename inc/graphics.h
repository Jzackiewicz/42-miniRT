/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:45:23 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/13 16:37:35 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "../lib/mlx/mlx.h"
# include <X11/keysym.h>
# include <stdlib.h>

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900

typedef struct s_mlx_data
{
	void		*mlx_ptr;
	void		*window_ptr;
	void		*img_ptr;
	char		*img_addr;
}				t_mlx_data;

typedef struct s_ray_tracer_data
{
	t_mlx_data	*mlx_data;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			x;
	int			y;

}				t_ray_tracer_data;

void			draw_pixel(t_ray_tracer_data *data, int x, int y, int color);
void			init_mlx(t_ray_tracer_data **ray_tracer_data);
int				close_window(t_ray_tracer_data *rt_data, int errno);
int				handle_key_input(int keysym, t_ray_tracer_data *rt_data);
void			free_window(t_mlx_data *mlx_data);
void			free_image(t_mlx_data *mlx_data);
void			clean_mlx(t_ray_tracer_data *rt_data);

#endif