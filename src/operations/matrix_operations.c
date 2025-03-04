/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:31:28 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/04 10:40:31 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/operations.h"

t_matrix	*multiply_matrices(t_matrix *matrix1, t_matrix *matrix2)
{
	int	i;
	int	j;
	t_matrix	*result;
	
	if (!matrix1 || !matrix2)
		return (NULL);
	if (matrix1->row != matrix2->col)
		return (NULL);
	result = init_matrix(matrix1->row, matrix2->col);
	if (!result)
		return (NULL);
	i = 0;
	while (i < matrix1->row)
	{
		while (j < matrix2->col)
		{
			
			j++;
		}
		i++;
	}
}