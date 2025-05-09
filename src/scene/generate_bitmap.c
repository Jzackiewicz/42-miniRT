/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_bitmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubaz <kubaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:02:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/05/02 00:41:16 by kubaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"
#include "../../inc/scene.h"

static int	**init_bitmap(void)
{
	int	i;
	int	j;
	int	**bitmap;

	bitmap = (int **)malloc(sizeof(int *) * WINDOW_HEIGHT);
	if (!bitmap)
		return (NULL);
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		bitmap[i] = (int *)malloc(sizeof(int) * WINDOW_WIDTH);
		if (!bitmap[i])
			return (NULL);
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			bitmap[i][j] = 0;
			j++;
		}
		i++;
	}
	return (bitmap);
}

int	**generate_bitmap(t_world *world)
{
	int		i;
	int		j;
	int		**bitmap;
	t_ray	*ray;
	int		color;

	bitmap = init_bitmap();
	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		j = -1;
		while (++j < WINDOW_WIDTH)
		{
			ray = ray_for_pixel(world->camera, j, i);
			color = color_at(world, ray);
			free_ray(ray);
			bitmap[i][j] = color;
		}
	}
	return (bitmap);
}

void	free_bitmap(int **bitmap)
{
	int	i;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		free(bitmap[i]);
		i++;
	}
	free(bitmap);
}
