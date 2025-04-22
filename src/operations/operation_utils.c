/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:26:02 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/22 16:31:31 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/operations.h"

int	compare_floats(double a, double b)
{
	double	epsilon;

	epsilon = 1e-6;
	return (fabs(a - b) < epsilon);
}

/* Creates a tuple filled with x, y, z
	w == 1: point{0, 0, 0, 1}
	w == 0: vector{0, 0, 0, 0} */
double	*init_tuple(double x, double y, double z, double w)
{
	double	*tuple;

	tuple = (double *)malloc(sizeof(double) * 4);
	if (!tuple)
		return (NULL);
	tuple[0] = x;
	tuple[1] = y;
	tuple[2] = z;
	tuple[3] = w;
	return (tuple);
}

double	*tupledup(double *tuple, int size)
{
	int		i;
	double	*new_tuple;

	new_tuple = (double *)malloc(sizeof(double) * size);
	if (!new_tuple)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_tuple[i] = tuple[i];
		i++;
	}
	return (new_tuple);
}

/* Debug */
void	print_tuple(double *tuple)
{
	if (!tuple)
	{
		printf("No tuple\n");
		return ;
	}
	if (compare_floats(tuple[3], 1))
		printf("Point: ");
	else if (compare_floats(tuple[3], 0))
		printf("Vector: ");
	else
	{
		printf("Tuple: ");
		printf("{%f, %f, %f, %f}\n", tuple[0], tuple[1], tuple[2], tuple[3]);
		return ;
	}
	printf("{%f, %f, %f}\n", tuple[0], tuple[1], tuple[2]);
}

/* Debug */
void	find_vector(double x, double y, double z)
{
	double	point[3];
	double	*zero_point;
	double	*vector;

	point[0] = x;
	point[1] = y;
	point[2] = z;
	zero_point = init_tuple(0, 0, 0, 1);
	vector = subtract_tuple(point, zero_point);
	normalize(&vector);
	print_tuple(vector);
}
