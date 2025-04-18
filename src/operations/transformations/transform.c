/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubaz <kubaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:19:19 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/18 19:35:45 by kubaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/operations.h"

/* Creates a 4x4 matrix that can move a point by tuple coords given as a
parameter.
Inverting transform matrix moves point in opposite direction
Translation doesn't affect vectors ({x, y, z, 0}).
Undefined behavior when tuple is not of size 3*/
t_matrix	*translation(double *tuple)
{
	t_matrix	*transform;

	if (!tuple)
		return (NULL);
	transform = create_identity_matrix(4, 4);
	if (!transform)
		return (NULL);
	transform->grid[0][3] = tuple[0];
	transform->grid[1][3] = tuple[1];
	transform->grid[2][3] = tuple[2];
	return (transform);
}

/* Creates a 4x4 matrix that after multiplication moves a tuple by
multiplying its coordinates by multiplier given as a parameter.
Also acts as reflecting when scaled by negative values.
Undefined behavior when tuple is not of size 3*/
t_matrix	*scaling(double mult_x, double mult_y, double mult_z)
{
	t_matrix	*transform;

	transform = create_identity_matrix(4, 4);
	if (!transform)
		return (NULL);
	transform->grid[0][0] = mult_x;
	transform->grid[1][1] = mult_y;
	transform->grid[2][2] = mult_z;
	return (transform);
}

/* Creates a 4x4 matrix that after multiplication moves a tuple by
multiplying its components by proportions to the other two components
given as a parameter.
Undefined behavior when tuple is not of size 6.
tuple = {xy, xz, yx, yz, zx, zy}*/
t_matrix	*shearing(double *tuple)
{
	t_matrix	*transform;

	if (!tuple)
		return (NULL);
	transform = create_identity_matrix(4, 4);
	if (!transform)
		return (NULL);
	transform->grid[0][1] = tuple[0];
	transform->grid[0][2] = tuple[1];
	transform->grid[1][0] = tuple[2];
	transform->grid[1][2] = tuple[3];
	transform->grid[2][0] = tuple[4];
	transform->grid[2][1] = tuple[5];
	return (transform);
}
