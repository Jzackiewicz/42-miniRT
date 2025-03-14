/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:52:22 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/13 12:53:07 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"

void	clean_intersect_memory(double *side_t, double *caps_t)
{
	if (side_t)
		free(side_t);
	if (caps_t)
		free(caps_t);
}

void	free_cylinder_resources(double *arr_t, double *oc_vector, double *quad)
{
	if (arr_t)
		free(arr_t);
	if (oc_vector)
		free(oc_vector);
	if (quad)
		free(quad);
}
