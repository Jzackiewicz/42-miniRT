/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:41:40 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/03 09:56:32 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "rays.h"

typedef struct s_world
{
	t_object	**objs;
	t_light		*light;
	t_ambient	*ambient;
	t_camera	*camera;
}				t_world;

t_ray			*ray_to_object_space(t_ray *ray, t_object *obj);
int				rgb_to_int(double r, double g, double b);
t_ray			*ray_for_pixel(t_camera *cam_data, int px, int py);

t_world			*create_world(t_input_data **input_data, int no_lines);

double			color_at(t_world *world, t_ray *ray);

int				**generate_bitmap(t_world *world);
void			free_bitmap(int **bitmap);

#endif