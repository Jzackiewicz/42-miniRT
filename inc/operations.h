/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:29:30 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/19 11:03:29 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "../lib/libft/libft.h"
# include <math.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

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
double		*subtract_tuple(double *tuple1, double *tuple2);
double		*negate_tuple(double *tuple);
double		*multiply_tuple(double *tuple, double scalar);
double		*divide_tuple(double *tuple, double scalar);
double		magnitude(double *vector);
void		normalize(double **vector);
double		dot(double *vector1, double *vector2);
double		*cross(double *vector1, double *vector2);

//			matrix_operations
t_matrix	*multiply_matrices(t_matrix *matrix1, t_matrix *matrix2);
double		*multiply_matrix_and_tuple(t_matrix *matrix, double *tuple);
void		transpose(t_matrix **matrix);
void		make_identity(t_matrix *matrix);

//			transformations
void		inverse(t_matrix *matrix);
t_matrix	*translation(double *tuple);
t_matrix	*scaling(double *tuple);
t_matrix	*shearing(double *tuple);
t_matrix	*rotation_x(double angle);
t_matrix	*rotation_y(double angle);
t_matrix	*rotation_z(double angle);

//			matrix_utils
t_matrix	*init_matrix(int row, int col);
t_matrix	*tuple_to_matrix(double *tuple);
void		free_matrix(t_matrix *matrix);
void		print_matrix(t_matrix *matrix);

// 			utils
int			compare_floats(double a, double b);
double		*init_tuple(int w);
void		print_tuple(double *tuple);

#endif