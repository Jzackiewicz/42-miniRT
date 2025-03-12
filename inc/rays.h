/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:34:08 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/12 15:03:49 by jzackiew         ###   ########.fr       */
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
}		t_ray;

t_ray	*create_ray(double *origin, double *direction);
double	*position(t_ray *ray, double t);
double	*intersect(t_object *obj, t_ray *ray);

#endif