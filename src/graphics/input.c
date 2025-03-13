/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:46:52 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/13 16:37:06 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/graphics.h"

int	handle_key_input(int keysym, t_ray_tracer_data *rt_data)
{
	if (keysym == XK_Escape)
		close_window(rt_data, 1);
	return (0);
}
