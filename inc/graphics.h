/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:45:23 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/16 16:54:54 by agarbacz         ###   ########.fr       */
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

typedef struct s_image
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_image;

typedef struct s_uv
{
	double				u;
	double				v;
}						t_uv;

typedef struct s_texture
{
	t_image *texel; // texture element
	t_image				*nmap;
	int					width;
	int					height;
	int					nwidth;
	int					nheight;
}						t_texture;

// 							RENDERING
void					render_image(t_ray_tracer_data *data, int **bitmap);

//							MLX_MANAGE
int						close_window(t_ray_tracer_data *rt_data, int errno);
int						handle_key_input(int keysym,
							t_ray_tracer_data *rt_data);
void					mlx_run(t_world *world_data, int no_lines,
							t_input_data **in_data);

// TEXTURES
typedef struct s_comps	t_comps;
t_texture				*create_image_texture(void *mlx, t_texture *texture,
							const char *path);
void					free_texture(t_ray_tracer_data *rt_data, t_object *obj);
t_uv					get_spherical_map(t_comps *comps);
t_uv					get_planar_map(t_comps *comps);
double					*get_texture_color(t_texture *texture, double u,
							double v);
#endif
