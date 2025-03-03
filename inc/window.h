/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:45:23 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/03 09:09:29 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

#include "../lib/mlx/mlx.h"
#include <stdlib.h>
#include <X11/keysym.h>

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

typedef struct s_mlx_data
{
	void		*mlx_ptr;
	void		*win_ptr;
}			t_mlx_data;

void	prepare_window(void);

#endif