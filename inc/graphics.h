/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:45:23 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/24 13:19:02 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

// SECTION: includes
# include "../lib/mlx/mlx.h"
# include "rays.h"
# include <X11/keysym.h>
# include <stdlib.h>

// SECTION: constants
# define WINDOW_WIDTH 500
# define WINDOW_HEIGHT 500

// SECTION: structs
typedef struct s_mlx_data
{
	void				*mlx_ptr;
	void				*window_ptr;
	void				*img_ptr;
	char				*img_addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_mlx_data;

typedef struct s_ray_tracer_data
{
	t_mlx_data			*mlx_data;
	int					x;
	int					y;
}						t_ray_tracer_data;

// SECTION: canvas and image utilities
typedef struct s_camera	t_camera;
double					get_canvas_width(t_camera *cam_data);

// SECTION: drawing utilities
void					draw_pixel(t_ray_tracer_data *data, int x, int y,
							int color);
void					render_image(t_ray_tracer_data *data, int **bitmap);

// SECTION: minilibx setup & cleanup
void					init_mlx(t_ray_tracer_data **rt_data);
void					clean_mlx(t_ray_tracer_data *rt_data);
int						close_window(t_ray_tracer_data *rt_data, int errno);
void					free_window(t_mlx_data *mlx_data);
void					free_image(t_mlx_data *mlx_data);
int						handle_key_input(int keysym,
							t_ray_tracer_data *rt_data);

// SECTION: main mlx fn
void					mlx_run(int **bitmap);


typedef struct s_object t_object;
int	**generate_new_bitmap(t_camera *cam_data, t_object **objs);

#endif
