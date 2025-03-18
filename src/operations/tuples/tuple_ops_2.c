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

#include "../../../inc/operations.h"

/* Returns length of a vector or -1.0 when *vector points to NULL */
double	magnitude(double *vector)
{
	double	result;
	size_t	i;

	if (!vector)
		return (-1);
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

/* Returns normalized vector */
void	normalize(double **vector)
{
	int		i;
	double	len;

	len = magnitude(*vector);
	if (!len)
		return ;
	i = 0;
	while (i < 3)
	{
		(*vector)[i] /= len;
		i++;
	}
}

/* Returns a dot product (scalar) of two vectors */
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

/* Returns a cross product (vector) of two vectors */
double	*cross(double *vector1, double *vector2)
{
	double	*result;

	if (!vector1 || !vector2)
		return (NULL);
	result = (double *)malloc(sizeof(double) * 4);
	if (!result)
		return (NULL);
	result[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
	result[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
	result[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
	result[3] = 0;
	return (result);
}
