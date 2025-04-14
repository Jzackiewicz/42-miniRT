/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:21:38 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/14 17:32:18 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

t_texture	*create_image_texture(void *mlx, t_texture *texture,
		const char *path)
{
	texture->texel.img = mlx_xpm_file_to_image(mlx, (char *)path,
			&texture->width, &texture->height);
	if (texture->texel.img)
	{
		texture->texel.addr = mlx_get_data_addr(texture->texel.img,
				&texture->texel.bits_per_pixel, &texture->texel.line_length,
				&texture->texel.endian);
		return (texture);
	}
	return (NULL);
}

t_texture	*apply_normal_map_to_texture(void *mlx_ptr, t_texture *texture,
		const char *path)
{
	texture->nmap.img = mlx_xpm_file_to_image(mlx_ptr, (char *)path,
			&texture->nwidth, &texture->nheight);
	if (texture->nmap.img)
	{
		if (texture->nwidth != texture->width
			|| texture->nheight != texture->height)
		{
			mlx_destroy_image(mlx_ptr, texture->nmap.img);
			texture->nmap.img = NULL;
		}
		else
		{
			texture->nmap.addr = mlx_get_data_addr(texture->nmap.img,
					&texture->nmap.bits_per_pixel, &texture->nmap.line_length,
					&texture->nmap.endian);
			return (texture);
		}
	}
	return (NULL);
}
double *get_texture_color(t_texture texture, double u, double v)
{
    double *color = malloc(sizeof(double) * 3);
    int x;
	int y;
    unsigned int pixel;
    
    x = (int)(u * (texture.width - 1)) % texture.width;
    y = (int)(v * (texture.height - 1)) % texture.height;
    pixel = *(unsigned int*)(texture.texel.addr + (y * texture.texel.line_length + 
            x * (texture.texel.bits_per_pixel / 8)));
    color[0] = ((pixel >> 16) & 0xFF);
    color[1] = ((pixel >> 8) & 0xFF);
    color[2] = (pixel & 0xFF);
    return (color);
}

void	apply_obj_texture(t_object *obj, t_texture texture)
{
	obj->texture = texture;
}
