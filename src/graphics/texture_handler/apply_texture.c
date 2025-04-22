/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:21:38 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/22 16:30:01 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

void	free_texture(t_ray_tracer_data *rt_data, t_object *obj)
{
	if (obj->texture)
	{
		mlx_destroy_image(rt_data->mlx_data->mlx_ptr, obj->texture->texel->img);
		free(obj->texture->texel);
		free(obj->texture->nmap);
	}
	free(obj->texture);
}

/**
 loads an XPM image into a t_texture struct.

 mlx: the mlx pointer
 texture: the t_texture struct to fill with the image data
 path: the path to the XPM image file

 returns the t_texture struct if successful, NULL otherwise
 */
t_texture	*create_image_texture(void *mlx_ptr, t_texture *texture,
		const char *path)
{
	texture = (t_texture *)malloc(sizeof(t_texture));
	texture->nmap = NULL;
	texture->texel = (t_image *)malloc(sizeof(t_image));
	texture->texel->img = mlx_xpm_file_to_image(mlx_ptr, (char *)path,
			&texture->width, &texture->height);
	if (texture->texel->img)
	{
		texture->texel->addr = mlx_get_data_addr(texture->texel->img,
				&texture->texel->bits_per_pixel, &texture->texel->line_length,
				&texture->texel->endian);
		return (texture);
	}
	mlx_destroy_image(mlx_ptr, texture->texel->img);
	free(texture);
	return (NULL);
}

/* unused for now */
t_texture	*apply_normal_map_to_texture(void *mlx_ptr, t_texture *texture,
		const char *path)
{
	texture->nmap = (t_image *)malloc(sizeof(t_image));
	texture->nmap->img = mlx_xpm_file_to_image(mlx_ptr, (char *)path,
			&texture->nwidth, &texture->nheight);
	if (texture->nmap->img)
	{
		if (texture->nwidth != texture->width
			|| texture->nheight != texture->height)
		{
			mlx_destroy_image(mlx_ptr, texture->nmap->img);
			texture->nmap->img = NULL;
		}
		else
		{
			texture->nmap->addr = mlx_get_data_addr(texture->nmap->img,
					&texture->nmap->bits_per_pixel, &texture->nmap->line_length,
					&texture->nmap->endian);
			return (texture);
		}
	}
	return (NULL);
}

/*
 retrieves the color at a given point (u, v) on a texture.

 u and v are coordinates in the range [0, 1] that represent the position
 on the texture. The function will return the RGB color at that point.

 if the texture is invalid, the function will return NULL.

 returns the RGB color at the given point, or NULL if the texture is invalid
 */
double	*get_texture_color(t_texture *texture, double u, double v)
{
	double			*color;
	int				x;
	int				y;
	unsigned int	pixel;

	x = (int)(u * (texture->width - 1)) % texture->width;
	y = (int)(v * (texture->height - 1)) % texture->height;
	pixel = *(unsigned int *)(texture->texel->addr + (y
				* texture->texel->line_length + x
				* (texture->texel->bits_per_pixel / 8)));
	color = malloc(sizeof(double) * 3);
	color[0] = ((pixel >> 16) & 0xFF);
	color[1] = ((pixel >> 8) & 0xFF);
	color[2] = (pixel & 0xFF);
	return (color);
}
