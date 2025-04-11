/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:51:39 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/11 12:25:57 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"
#include "../../inc/rays.h"

void	free_input_ids(t_input_data **input_data)
{
	int	i;

	i = 0;
	while (input_data[i])
	{
		if (!ft_strncmp(input_data[i]->id, "A\0", 2)
			|| !ft_strncmp(input_data[i]->id, "C\0", 2)
			|| !ft_strncmp(input_data[i]->id, "L\0", 2))
			free(input_data[i]->id);
		i++;
	}
}

void	free_comps(t_comps *comps)
{
	free(comps->point);
	free(comps->eyev);
	free(comps->normalv);
	free(comps->over_point);
	free(comps);
}
