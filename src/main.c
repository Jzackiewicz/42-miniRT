/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:02:41 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/07 17:57:21 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(void)
{
	double p[] = {3, 2, 3};
	double skew[] = {0, 0, 1, 1, 0, 0};
	t_matrix *transform;
	double *result;

	transform = shearing(skew);
	print_matrix(transform);
	result = multiply_matrix_and_tuple(transform, p);
	for (int i = 0; i < transform->row; i++)
	{
		printf("result[%d]: %f\n", i, result[i]);
	}
	free_matrix(transform);
	free(result);
	return (0);
}