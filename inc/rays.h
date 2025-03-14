/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:34:08 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/14 16:05:08 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

# include "../lib/libft/libft.h"
# include "operations.h"
# include "parser.h"

typedef struct s_ray // xD
{
	double *origin;
	double *direction;
	double t;
}						t_ray;

typedef struct s_intersec
{
	double				t;
	struct s_object		*object;
}						t_intersec;

typedef struct s_object	t_object;

t_ray					*create_ray(double *origin, double *direction);
double					*position(t_ray *ray, double t);
// double			*init_cylinder_quad(t_input_data *obj, t_ray *ray,
// 					double *oc_vector);
// void			free_cylinder_resources(double *arr_t, double *oc_vector,
// 					double *quad);
// double			*init_result_t(void);
// double			*init_cylinder_quad(t_input_data *obj, t_ray *ray,
// 					double *oc_vector);
// double			check_height_constraints(t_input_data *obj, t_ray *ray,
// 					double *oc_vector, double t);
// int				check_cylinder_discriminant(double *quad, double **arr_t,
// 					double *oc_vector);
// double			*calculate_intersection_points(t_input_data *obj,
// t_ray *ray,
// 					double *oc_vector, double *quad);
// void			find_closest_t(double *side_t, double *caps_t, double *t1,
// 					double *t2);
// double			*intersect_cylinder(t_input_data *obj, t_ray *ray);
// void			clean_intersect_memory(double *side_t, double *caps_t);
// void			free_cylinder_resources(double *arr_t, double *oc_vector,
// 					double *quad);

double					*intersect(t_object *obj, t_ray *ray);
void					append_intersec(t_intersec **all, double *arr_t,
							t_object *obj, int intersec_no);
void					sort_intersections(t_intersec **i_s, int start_index,
							int end_index);
double					*identify_hit(t_ray *ray, t_intersec **i_s);

#endif