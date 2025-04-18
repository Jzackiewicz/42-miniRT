/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubaz <kubaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:22:46 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/18 19:34:54 by kubaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/operations.h"

/* Creates a 4x4 matrix that will rotate tuple by angle in x-axis when
multiplied. */
t_matrix	*rotation_x(double angle)
{
	t_matrix	*transform;

	transform = create_identity_matrix(4, 4);
	if (!transform)
		return (NULL);
	transform->grid[1][1] = cos(angle);
	transform->grid[2][1] = sin(angle);
	transform->grid[1][2] = -sin(angle);
	transform->grid[2][2] = cos(angle);
	return (transform);
}

/* Creates a 4x4 matrix that will rotate tuple by angle in y-axis when
multiplied. */
t_matrix	*rotation_y(double angle)
{
	t_matrix	*transform;

	transform = create_identity_matrix(4, 4);
	if (!transform)
		return (NULL);
	transform->grid[0][0] = cos(angle);
	transform->grid[0][2] = sin(angle);
	transform->grid[2][0] = -sin(angle);
	transform->grid[2][2] = cos(angle);
	return (transform);
}

/* Creates a 4x4 matrix that will rotate tuple by angle in z-axis when
multiplied. */
t_matrix	*rotation_z(double angle)
{
	t_matrix	*transform;

	transform = create_identity_matrix(4, 4);
	if (!transform)
		return (NULL);
	transform->grid[0][0] = cos(angle);
	transform->grid[1][0] = sin(angle);
	transform->grid[0][1] = -sin(angle);
	transform->grid[1][1] = cos(angle);
	return (transform);
}
