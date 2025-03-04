/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:31:28 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/04 17:04:10 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/operations.h"

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
	free_matrix(matrix);
	return (result);
}

t_matrix	*submatrix(t_matrix *matrix, int row, int col)
{
	t_matrix	*submatrix;
	int			i;
	int			j;
	int			k;
	int			l;

	if (!matrix || row < 0 || row > matrix->row || col < 0
			|| row > matrix->col)
		return (NULL);
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

int	main(void)
{
	t_matrix *m1, *m2, *r, *s;

	m1 = init_matrix(5, 4);
	// m2 = init_matrix(3, 4);

	for (int i = 0; i < m1->row; i++)
	{
		for (int j = 0; j < m1->col; j++)
			m1->grid[i][j] = (i + 1) + i * j;
	}
	// for (int i = 0; i < m2->row; i++)
	// {
	// 	for (int j = 0; j < m2->col; j++)
	// 		m2->grid[i][j] = (i * j + 3);
	// }
	// printf("m1: \n");
	// print_matrix(m1);
	// printf("m2: \n");
	// print_matrix(m2);
	// printf("r: \n");
	// r = multiply_matrices(m1, m2);
	// print_matrix(r);
	// printf("transposed: \n");
	// r = transpose(r);
	// print_matrix(r);
	printf("m1: \n");
	print_matrix(m1);
	printf("submatrix: \n");
	s = submatrix(m1, 3, 0);
	print_matrix(s);
	// free_matrix(m1);
	// free_matrix(m2);
	// free_matrix(r);
}