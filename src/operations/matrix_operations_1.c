/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:31:00 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/05 16:37:00 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/operations.h"

t_matrix	*tuple_to_matrix(double *tuple)
{
	t_matrix	*matrix;
	int			i;

	if (!tuple)
		return (NULL);
	matrix = init_matrix(1, 4);
	i = -1;
	while (++i < 4)
		matrix->grid[0][i] = tuple[i];
	return (matrix);
}

t_matrix	*multiply_matrices(t_matrix *matrix1, t_matrix *matrix2)
{
	int			i;
	int			j;
	int			k;
	t_matrix	*result;

	if (!matrix1 || !matrix2)
		return (NULL);
	if (matrix1->col != matrix2->row)
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
		}
	}
	return (result);
}

t_matrix	*transpose(t_matrix *matrix)
{
	t_matrix	*result;
	int			i;
	int			j;

	if (!matrix)
		return (NULL);
	result = init_matrix(matrix->col, matrix->row);
	i = 0;
	while (i < matrix->col)
	{
		j = 0;
		while (j < matrix->row)
		{
			result->grid[i][j] = matrix->grid[j][i];
			j++;
		}
		i++;
	}
	return (result);
}

void	identify(t_matrix *matrix)
{
	int	i;
	int	j;

	if (!matrix)
		return ;
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
}
