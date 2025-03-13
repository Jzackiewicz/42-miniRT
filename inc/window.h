/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:45:23 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/13 13:03:52 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "../lib/mlx/mlx.h"
# include <X11/keysym.h>
# include <stdlib.h>

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900

typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}			t_mlx_data;

void		prepare_window(void);

#endif