/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:40:15 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/03 18:38:46 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/operations.h"

/* Returns a tuple which is a result of adding two tuples.
Undefined behaviour when tuples have different length than 4 */
double	*add_tuple(double *tuple1, double *tuple2)
{
	size_t	i;
	double	*result;

	if (!tuple1 || !tuple2)
		return (NULL);
	result = (double *)malloc(sizeof(double) * 4);
	if (!result)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		result[i] = tuple1[i] + tuple2[i];
		i++;
	}
	if ((result[3] - 2.0) < 0.01 && (result[3] - 2.0) > -0.01)
		result[3] = 1.0;
	return (result);
}

/* Returns a tuple which is a result of substracting two tuples.
Undefined behaviour when tuples have different length than 4 */
double	*subtract_tuple(double *tuple1, double *tuple2)
{
	size_t	i;
	double	*result;

	if (!tuple1 || !tuple2)
		return (NULL);
	result = (double *)malloc(sizeof(double) * 4);
	if (!result)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		result[i] = tuple1[i] - tuple2[i];
		i++;
	}
	if ((result[3] + 1.0) < 0.01 && (result[3] + 1.0) > -0.01)
		result[3] = 1.0;
	return (result);
}

/* Returns negated tuple.
Undefined behaviour when given tuple has different length than 4 */
double	*negate_tuple(double *tuple)
{
	size_t	i;
	double	*result;

	if (!tuple)
		return (NULL);
	result = (double *)malloc(sizeof(double) * 4);
	if (!result)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		result[i] = -tuple[i];
		i++;
	}
	result[i] = tuple[i];
	return (result);
}

/* Returns a tuple which is a result of multiplying tuple by scalar.
Undefined behaviour when given tuple has different length than 4 */
double	*multiply_tuple(double *tuple, double scalar)
{
	size_t	i;
	double	*result;

	if (!tuple)
		return (NULL);
	result = (double *)malloc(sizeof(double) * 4);
	if (!result)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		result[i] = tuple[i] * scalar;
		i++;
	}
	result[i] = tuple[i];
	return (result);
}

/* Returns a tuple which is a result of dividing tuple by scalar.
Undefined behaviour when given tuple has different length than 4 */
double	*divide_tuple(double *tuple, double scalar)
{
	size_t	i;
	double	*result;

	if (!tuple)
		return (NULL);
	result = (double *)malloc(sizeof(double) * 4);
	if (!result)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		result[i] = tuple[i] / scalar;
		i++;
	}
	result[i] = tuple[i];
	return (result);
}
