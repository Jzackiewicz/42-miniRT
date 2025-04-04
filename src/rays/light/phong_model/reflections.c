/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:37:17 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/04 17:47:57 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/miniRT.h"

double	*find_reflection(double *lightp, double *normal, double *objectp)
{
	double	*lightv;
	double	*reflection;
	double	*tmp;

	lightv = subtract_tuple(lightp, objectp);
	normalize(&lightv);
	if (dot(lightv, normal) < 0)
		return (free(lightv), NULL);
	tmp = multiply_tuple(normal, 2 * dot(lightv, normal));
	reflection = subtract_tuple(lightv, tmp);
	free(tmp);
	free(lightv);
	return (reflection);
}
