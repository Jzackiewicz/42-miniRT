/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:29:30 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/05 12:32:34 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "../lib/libft/libft.h"
# include <math.h>

typedef struct s_matrix
{
	int		row;
	int		col;
	double	**grid;
}			t_matrix;

// POINT is a 4-element array where arr[3] = 1 -> (3, -3, 12, 1)
// VECTOR is a 4-element array where arr[3] = 0 -> (3, -3, 12, 0)

//			tuple_operations
double		*add_tuple(double *tuple1, double *tuple2);
double		*substract_tuple(double *tuple1, double *tuple2);
double		*negate_tuple(double *tuple);
double		*multiply_tuple(double *tuple, double scalar);
double		*divide_tuple(double *tuple, double scalar);
double		magnitude(double *vector);
double		*normalize(double *vector);
double		dot(double *vector1, double *vector2);
double		*cross(double *vector1, double *vector2);

//			matrix_operations
t_matrix	*multiply_matrices(t_matrix *matrix1, t_matrix *matrix2);
void		transpose(t_matrix *matrix);
t_matrix	*inverse(t_matrix *matrix);

//			utils
t_matrix	*init_matrix(int row, int col);
void		free_matrix(t_matrix *matrix);
void		print_matrix(t_matrix *matrix);
#endif