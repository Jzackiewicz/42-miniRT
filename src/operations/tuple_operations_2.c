/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:39:37 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/03 19:49:43 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/operations.h"

double	magnitude(double *vector)
{
	double	result;
	size_t	i;

	i = 0;
	result = 0;
	while (i < 3)
	{
		result += vector[i] * vector[i];
		i++;
	}
	result = sqrt(result);
	return (result);
}

double	*normalize(double *vector)
{
	double	*result;
	size_t	i;

	i = 0;
	result = divide_tuple(vector, magnitude(vector));
	return (result);
}

double	dot(double *vector1, double *vector2)
{
	double	result;
	size_t	i;

	if (!vector1 || !vector2)
		return (-1);
	i = 0;
	result = 0;
	while (i < 3)
	{
		result += vector1[i] * vector2[i];
		i++;
	}
	return (result);
}

double	*cross(double *vector1, double *vector2)
{
	size_t	i;
	double	*result;

	if (!vector1 || !vector2)
		return (NULL);
	result = (double *)malloc(sizeof(double) * 4);
	if (!result)
		return (NULL);
	i = 0;
	result[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
	result[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
	result[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
	result[3] = 0;
	return (result);
}

/* int	main(void)
{
	double t1[] = {18.24, 1.123, -123.2, 0};
	double t2[] = {4, 3, 2, 0};
	double *r;
	double x;

	r = normalize(t1);
	printf("\nnormalizacja: ");
	for (int i = 0; i < 3; i++)
	{
		printf("%f ", r[i]);
	}
	x = magnitude(r);
	printf("\n dlugosc znormalizowanego ziuta: %f\n", x);

	printf("\ncross: ");
	r = cross(t1, t2);
	for (int i = 0; i < 3; i++)
	{
		printf("%f ", r[i]);
	}
	return (0);
} */