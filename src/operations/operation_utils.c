/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:26:02 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/18 18:40:01 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/operations.h"

int	compare_floats(double a, double b)
{
	double	epsilon;

	epsilon = 1e-6;
	return (fabs(a - b) < epsilon);
}

/* Creates a tuple filled with zeros
	w == 1: point{0, 0, 0, 1}
	w == 0: vector{0, 0, 0, 0} */
double	*init_tuple(int w)
{
	int	i;
	double	*tuple;
	
	tuple = (double *)malloc(sizeof(double) * 4);
	if (!tuple)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		tuple[i] = 0;
		i++;
	}
	tuple[i] = w;
	return (tuple);
}

void	print_tuple(double *tuple)
{
	if (compare_floats(tuple[3], 1))
		printf("Point: ");
	else if (compare_floats(tuple[3], 0))
		printf("Vector: ");
	else
		printf("Tuple: ");
	printf("{%f, %f, %f}\n", tuple[0], tuple[1], tuple[2]);
}