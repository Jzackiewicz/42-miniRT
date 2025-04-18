/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubaz <kubaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:31:00 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/18 19:37:34 by kubaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/operations.h"

/* Returns matrix that is a result of matrix1 * matrix2 */
t_matrix	*multiply_matrices(t_matrix *matrix1, t_matrix *matrix2)
{
	int			i;
	int			j;
	int			k;
	t_matrix	*result;

	if (!matrix1 || !matrix2 || matrix1->col != matrix2->row)
		return (NULL);
	result = init_matrix(matrix1->row, matrix2->col);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < matrix1->row)
	{
		j = -1;
		while (++j < matrix2->col)
		{
			k = -1;
			while (++k < matrix1->col)
				result->grid[i][j] += matrix1->grid[i][k] * matrix2->grid[k][j];
			if (compare_floats(result->grid[i][j], 0.0))
				result->grid[i][j] = 0;
		}
	}
	return (result);
}

/* Returns a tuple that is a result of multiplying matrix and tuple.
Undefined behaviour when tuple len is not the same as number of columns */
double	*multiply_tuple_and_matrix(t_matrix *matrix, double *tuple)
{
	int		i;
	int		j;
	double	*result;

	if (!matrix || !tuple)
		return (NULL);
	result = init_tuple(0, 0, 0, tuple[3]);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < matrix->row)
	{
		j = -1;
		while (++j < matrix->col)
			result[i] += matrix->grid[i][j] * tuple[j];
	}
	result[3] = tuple[3];
	return (result);
}

/* Changes any n * m matrix into m * n matrix */
void	transpose(t_matrix **matrix)
{
	t_matrix	*result;
	int			i;
	int			j;

	if (!matrix || !*matrix)
		return ;
	result = init_matrix((*matrix)->col, (*matrix)->row);
	i = 0;
	while (i < (*matrix)->col)
	{
		j = 0;
		while (j < (*matrix)->row)
		{
			result->grid[i][j] = (*matrix)->grid[j][i];
			j++;
		}
		i++;
	}
	free_matrix(*matrix);
	*matrix = result;
}

/* Turns any square matrix into indentity matrix */
t_matrix	*create_identity_matrix(int row, int col)
{
	int			i;
	int			j;
	t_matrix	*matrix;
	
	matrix = init_matrix(row, col);
	if (!matrix || matrix->row != matrix->col)
		return (NULL);
	i = 0;
	while (i < matrix->row)
	{
		j = 0;
		while (j < matrix->col)
		{
			if (i == j)
				matrix->grid[i][j] = 1;
			else
				matrix->grid[i][j] = 0;
			j++;
		}
		i++;
	}
	return (matrix);
}
