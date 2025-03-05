/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfomations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:19:19 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/05 18:11:26 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/operations.h"

t_matrix	*translation(double *point)
{
	t_matrix	*transform;
	t_matrix	*point_matrix;
	
	if (!point)
		return (NULL);
	transform = init_matrix(4, 4);
	if (!transform)
		return (NULL);
	identify(transform);
	transform->grid[0][3] = point[0];	
	transform->grid[1][3] = point[1];
	transform->grid[2][3] = point[2];
	return (transform);
}

t_matrix	*scaling(double *point)
{
	t_matrix	*transform;
	t_matrix	*point_matrix;
	
	if (!point)
		return (NULL);
	transform = init_matrix(4, 4);
	if (!transform)
		return (NULL);
	identify(transform);
	transform->grid[0][0] = point[0];	
	transform->grid[1][1] = point[1];
	transform->grid[2][2] = point[2];
	print_matrix(transform);
	return (transform);
	
}

int main()
{
	double	p[] = {3, -2, -0.5, 0};
	double	t[] = {0.5, 2, 3};
	t_matrix	*p_m;
	t_matrix	*transform;
	t_matrix	*result;
	t_matrix	*tmp;
	
	transform = scaling(t);
	tmp = tuple_to_matrix(p);
	p_m = transpose(tmp);
	free_matrix(tmp);
	result = multiply_matrices(transform, p_m);
	print_matrix(result);
}