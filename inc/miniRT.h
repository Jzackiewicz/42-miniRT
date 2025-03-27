/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:58:11 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/27 17:53:27 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/libft/libft.h"
# include "graphics.h"
# include "operations.h"
# include "data_processing.h"
# include "rays.h"
# include <math.h>
# include <stdbool.h>

typedef struct s_comps
{
	double			t;
	t_object		*obj;
	double			*point;
	double			*eyev;
	double			*normalv;
	bool			inside;
}					t_comps;

typedef struct s_world
{
	t_object		**objs;
	t_light			*light;
	t_ambient		*ambient;
	t_camera		*camera;

}					t_world;

typedef struct s_material
{
	double			ambient;
	double			diffuse;
	double			specular;
	double			shininess;

}					t_material;

typedef struct s_object
{
	char			*id;
	double			diameter;
	double			height;
	int				*color;
	double			*coords;
	double			*orientation_vector;
	struct s_matrix	*transform;
	struct s_matrix	*inv_transform;
	t_material		*material;
}					t_object;

typedef struct s_camera
{
	double			*origin;
	double			*orientation_vector;
	double			fov;
	struct s_matrix	*transform;
	struct s_matrix	*inv_transform;
	double			half_width;
	double			half_height;
	double			pixel_size;
}					t_camera;

typedef struct s_light
{
	double			*coords;
	double			brightness;
	int				*color;
}					t_light;

typedef struct s_ambient
{
	double			brightness;
	int				*color;
}					t_ambient;

void				free_intersections(t_intersec **ray_intersex);
void				clean_rays(t_ray **rays);
void				free_objects(t_input_data **inp_data, t_object **objs,
						int no_lines);
void				free_bitmap(int **bitmap);
void				clean_objects(t_object **objs, t_input_data **data,
						int no_lines);

t_world				*create_world(t_camera *cam_data, t_light *light,
						t_ambient *ambient, t_object **objs);

double				color_at(t_world *world, t_ray *ray);

#endif