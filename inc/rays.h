/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:34:08 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/31 11:46:58 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

# include "../lib/libft/libft.h"
# include "data_processing.h"
# include "graphics.h"
# include "operations.h"

typedef struct s_ray // xD
{
	double *origin;
	double *direction;
}						t_ray;

typedef struct s_intersec
{
	double				t;
	struct s_object		*object;
}						t_intersec;

typedef struct s_light	t_light;
typedef struct s_object	t_object;
typedef struct s_camera	t_camera;

t_ray					*create_ray(double *origin, double *direction);
void					free_ray(t_ray *ray);
double					*position(t_ray *ray, double t);
double					*intersect(t_object *obj, t_ray *ray);
void					sort_intersections(t_intersec **i_s, int start_index,
							int end_index);
t_intersec				**get_sorted_intersections(t_ray *ray, t_object **objs);
t_intersec				*identify_hit(t_intersec **i_s);

//				spacial_conversion

typedef struct s_light	t_light;

// light section
double					*get_normal_at(t_object *obj, double *w_point);
double					*reflect(double *in, double *normal);
double					lighting(t_light *light, t_object *obj,
							t_camera *cam_data, t_ambient *ambient_data,
							double *normal, double *point);

void					free_intersections(t_intersec **ray_intersex);
#endif