/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:26:02 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/11 11:39:48 by jzackiew         ###   ########.fr       */
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
	int		i;
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

double	*tupledup(double *tuple)
{
	int		i;
	double	*new_tuple;

	new_tuple = (double *)malloc(sizeof(double) * 4);
	if (!new_tuple)
		return (NULL);
	i = 0;
	while (i < 4)
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
	double point[3];
	double	*zero_point;
	double	*vector;
	
	point[0] = x;
	point[1] = y;
	point[2] = z;
	zero_point = init_tuple(1);
	vector = subtract_tuple(point, zero_point);
	normalize(&vector);
	print_tuple(vector);
}
