/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:29:30 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/03 19:51:09 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

# include <math.h>
# include "../lib/libft/libft.h"

//POINT is a 4-element array where arr[3] = 1 -> (3, -3, 12, 1)
//VECTOR is a 4-element array where arr[3] = 0 -> (3, -3, 12, 0)

double	*add_tuple(double *tuple1, double *tuple2);
double	*substract_tuple(double *tuple1, double *tuple2);
double	*negate_tuple(double *tuple);
double	*multiply_tuple_scalar(double *tuple, double scalar);
double	*divide_tuple_scalar(double *tuple, double scalar);
double	magnitude(double *vector);
double	*normalize(double *vector);
double	dot(double *vector1, double *vector2);
double	*cross(double *vector1, double *vector2);
#endif