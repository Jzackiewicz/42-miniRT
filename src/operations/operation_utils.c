/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:26:02 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/18 11:23:25 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/operations.h"

int	compare_floats(double a, double b)
{
	double	epsilon;

	epsilon = 1e-6;
	return (fabs(a - b) < epsilon);
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
