/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:40:56 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/19 11:36:10 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/operations.h"

/* Creates new row * col matrix filled with zeros */
t_matrix	*init_matrix(int row, int col)
{
	t_matrix	*matrix;
	int			i;
	int			j;

	matrix = (t_matrix *)malloc(sizeof(t_matrix));
	if (!matrix)
		return (NULL);
	matrix->row = row;
	matrix->col = col;
	matrix->grid = (double **)malloc(sizeof(double *) * row);
	if (!matrix->grid)
		return (NULL);
	i = -1;
	while (++i < row)
	{
		matrix->grid[i] = (double *)malloc(sizeof(double) * col);
		if (!matrix->grid[i])
			return (NULL);
		j = -1;
		while (++j < col)
			matrix->grid[i][j] = 0;
	}
	return (matrix);
}

/* Returns a 1x4 matrix from 4-element tuple.
Other tuples sizes are not defined. */
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

void	free_matrix(t_matrix *matrix)
{
	int	i;

	i = 0;
	while (i < matrix->row)
	{
		free(matrix->grid[i]);
		i++;
	}
	free(matrix->grid);
	free(matrix);
}

void	print_matrix(t_matrix *matrix)
{
	int	i;
	int	j;

	if (!matrix)
	{
		printf("Error - No matrix\n");
		return ;
	}
	printf("{");
	i = -1;
	while (++i < matrix->row)
	{
		printf("{");
		j = -1;
		while (++j < matrix->col)
		{
			printf("%f", matrix->grid[i][j]);
			if (j != matrix->col - 1)
				printf(",");
		}
		printf("}");
		if (i != matrix->row - 1)
			printf(",\n");
	}
	printf("}\n");
}
