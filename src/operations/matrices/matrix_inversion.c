/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:31:28 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/07 12:28:21 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/operations.h"

static double	cofactor(t_matrix *matrix, int row, int col);

static t_matrix	*submatrix(t_matrix *matrix, int row, int col)
{
	t_matrix	*submatrix;
	int			i;
	int			j;
	int			k;
	int			l;

	submatrix = init_matrix(matrix->row - 1, matrix->col - 1);
	i = -1;
	k = 0;
	while (++i < matrix->row)
	{
		if (i == row)
			continue ;
		j = -1;
		l = 0;
		while (++j < matrix->col)
		{
			if (j == col)
				continue ;
			submatrix->grid[k][l++] = matrix->grid[i][j];
		}
		k++;
	}
	return (submatrix);
}

static double	determinant(t_matrix *matrix)
{
	float	det;
	int		i;

	if (!matrix || matrix->row != matrix->col)
		return (-1);
	det = 0;
	if (matrix->row == 1 && matrix->row == 1)
		det = matrix->grid[0][0];
	else if (matrix->row == 2 && matrix->row == 2)
		det = matrix->grid[0][0] * matrix->grid[1][1] - matrix->grid[0][1]
			* matrix->grid[1][0];
	else
	{
		i = -1;
		while (++i < matrix->col)
			det += matrix->grid[0][i] * cofactor(matrix, 0, i);
	}
	return (det);
}

static double	minor(t_matrix *matrix, int row, int col)
{
	t_matrix	*tmp_submatrix;
	double		minor;

	tmp_submatrix = submatrix(matrix, row, col);
	minor = determinant(tmp_submatrix);
	free_matrix(tmp_submatrix);
	return (minor);
}

static double	cofactor(t_matrix *matrix, int row, int col)
{
	double	min;
	double	cof;

	if (!matrix)
		return (-1);
	min = minor(matrix, row, col);
	if ((row + col) % 2 != 0)
		cof = -1 * min;
	else
		cof = min;
	return (cof);
}

t_matrix	*inverse(t_matrix *matrix)
{
	t_matrix	*inverted;
	double		det;
	int			i;
	int			j;

	if (!matrix || matrix->row != matrix->col)
		return (NULL);
	det = determinant(matrix);
	if (det == 0)
		return (NULL);
	inverted = init_matrix(matrix->row, matrix->col);
	if (!inverted)
		return (NULL);
	i = -1;
	while (++i < matrix->row)
	{
		j = -1;
		while (++j < matrix->col)
			inverted->grid[j][i] = cofactor(matrix, i, j) / det;
	}
	return (inverted);
}
