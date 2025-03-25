/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:46:52 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/25 12:25:22 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/graphics.h"

int	handle_key_input(int keysym, t_ray_tracer_data *rt_data)
{
	if (keysym == XK_Escape)
		close_window(rt_data, 0);
	return (0);
}
