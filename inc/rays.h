/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:34:08 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/20 12:55:34 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

# include "../lib/libft/libft.h"
# include "graphics.h"
# include "operations.h"
# include "parser.h"

typedef struct s_ray // xD
{
	double	*origin;
	double	*direction;
}						t_ray;

typedef struct s_intersec
{
	double				t;
	struct s_object		*object;
}						t_intersec;

typedef struct s_object	t_object;
typedef struct s_camera	t_camera;

t_ray					*create_ray(double *origin, double *direction);
t_ray					**generate_rays(t_camera *cam_data);
double					*position(t_ray *ray, double t);
double					*intersect(t_object *obj, t_ray *ray);
void					sort_intersections(t_intersec **i_s, int start_index,
							int end_index);
t_intersec				**get_sorted_intersections(t_ray *ray, t_object **objs);
t_intersec				*identify_hit(t_intersec **i_s);
t_intersec				***find_all_intersections(t_ray **rays,
							t_object **objs);
int						count_intersections(t_intersec **intersex);
int						**generate_bitmap(t_intersec ***ray_intersections,
							t_ray **rays, t_camera *cam_data);


//				spacial_conversion
t_ray	*ray_to_object_space(t_ray *ray, t_object *obj);

// light section
double	*get_normal_at(t_object *obj, double *w_point);

#endif