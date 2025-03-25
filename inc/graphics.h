/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:45:23 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/25 12:55:38 by jzackiew         ###   ########.fr       */
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

// 						RENDERING
void					render_image(t_ray_tracer_data *data, int **bitmap);

//						MLX_MANAGE
int						close_window(t_ray_tracer_data *rt_data, int errno);
int						handle_key_input(int keysym,
							t_ray_tracer_data *rt_data);
void					mlx_run(int **bitmap);


typedef struct s_object	t_object;
typedef struct s_light	t_light;
typedef struct s_camera	t_camera;
typedef struct s_ambient	t_ambient;
int	**generate_bitmap(t_camera *cam_data, t_object **objs,
	t_light *light_data, t_ambient *ambient_data);

#endif
