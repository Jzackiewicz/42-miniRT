/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:45:23 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/11 12:52:31 by jzackiew         ###   ########.fr       */
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
# define WINDOW_WIDTH 700
# define WINDOW_HEIGHT 700

// SECTION: structs
typedef struct s_mlx_data
{
	void					*mlx_ptr;
	void					*window_ptr;
	void					*img_ptr;
	char					*img_addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
}							t_mlx_data;

typedef struct s_ray_tracer_data
{
	t_mlx_data				*mlx_data;
	int						x;
	int						y;
}							t_ray_tracer_data;

// 							RENDERING
void						render_image(t_ray_tracer_data *data, int **bitmap);

//							MLX_MANAGE
int							close_window(t_ray_tracer_data *rt_data, int errno);
int							handle_key_input(int keysym,
								t_ray_tracer_data *rt_data);
void						mlx_run(int **bitmap);

#endif
