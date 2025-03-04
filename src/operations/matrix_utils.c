/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:40:56 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/04 17:00:06 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/operations.h"

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

	i = 0;
	if (!matrix)
	{
		printf("Error - No matrix\n");
		return ;	
	}
	while (i < matrix->row)
	{
		j = 0;
		while (j < matrix->col)
		{
			printf("| %f ", matrix->grid[i][j]);
			j++;
		}
		printf("|\n");
		i++;
	}
}

/* int	main(void)
{
	t_matrix *test;

	test = init_matrix(2, 7);
	print_matrix(test);
	free_matrix(test);
} */