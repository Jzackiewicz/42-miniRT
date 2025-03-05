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

#include "../../inc/operations.h"

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
	if ((result[3] - 2.0) < 0.1 && (result[3] - 2.0) > -0.1)
		result[3] = 1.0;
	return (result);
}

double	*substract_tuple(double *tuple1, double *tuple2)
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
	if ((result[3] + 1.0) < 0.1 && (result[3] + 1.0) > -0.1)
		result[3] = 1.0;
	return (result);
}

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

/* int main()
{
	double t1[] = {18.24, 1.123, -123.2, 1};
	double t2[] = {4, 3, 2, 0};
	double *r;

	r = add_tuple(t1, t2);
	printf("dodawanie: ");
	for (int i = 0; i < 4; i++)
	{
		printf("%f ", r[i]);
	}
	r = substract_tuple(t2, t1);
	printf("\nodejmowanie: ");
	for (int i = 0; i < 4; i++)
	{
		printf("%f ", r[i]);
	}
	r = negate_tuple(t2);
	printf("\nniggacja: ");
	for (int i = 0; i < 4; i++)
	{
		printf("%f ", r[i]);
	}
	r = multiply_tuple(t1, 2.5);
	printf("\nmnożenie: ");
	for (int i = 0; i < 4; i++)
	{
		printf("%f ", r[i]);
	}
	r = divide_tuple(t1, 3);
	printf("\ndzielenie: ");
	for (int i = 0; i < 4; i++)
	{
		printf("%f ", r[i]);
	}
} */