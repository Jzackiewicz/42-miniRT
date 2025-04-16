/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:36:23 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/16 17:51:26 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"

int	get_no_obj_elems(t_input_data **data)
{
	int	i;
	int	no_elems;

	i = -1;
	no_elems = 0;
	while (data[++i])
	{
		if (!ft_strncmp(data[i]->id, "sp\0", 3) || !ft_strncmp(data[i]->id,
				"cy\0", 3) || !ft_strncmp(data[i]->id, "pl\0", 3))
			no_elems++;
	}
	return (no_elems);
}

int	get_no_light_elems(t_input_data **data)
{
	int	i;
	int	no_elems;

	i = -1;
	no_elems = 0;
	while (data[++i])
	{
		if (!ft_strncmp(data[i]->id, "L\0", 2))
			no_elems++;
	}
	return (no_elems);
}
