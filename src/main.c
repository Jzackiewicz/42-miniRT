/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:02:41 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/14 13:10:45 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// TODO: properly analyze and test the intersection calculations
// norminette with ray management
// find out what to do next lol

/* int	main(void)
{
	t_ray_tracer_data *rt_data;
	
	rt_data = NULL;
	init_mlx(&rt_data);
	render_image(rt_data);
	mlx_key_hook(rt_data->mlx_data->window_ptr, handle_key_input, rt_data);
	mlx_hook(rt_data->mlx_data->window_ptr, 17, 0, close_window, rt_data);
	mlx_loop(rt_data->mlx_data->mlx_ptr);
	clean_mlx(rt_data);
	return (0);
} */

int main()
{
	t_ray *ray;
	double o[] = {30.0, 0.0, 30.0, 1.0};
	double d[] = {1.0, 0.0, 0.0, 0.0};
	double			*arr_t;
	t_input_data	**data;
	t_object		**objs;
	t_intersec	**ray_intersex;
	int			no_lines;
	
	data = NULL;
	no_lines = parse_file("tests/integration_tests/testfiles/valid_nocy.rt",
			&data);
	objs = get_objects(data, no_lines);
	if (no_lines == -1)
	{
		printf("Error: file error\n");
		return (-1);
	}
	ray = create_ray(o, d);
	ray_intersex = (t_intersec **)ft_calloc((no_lines - 3) * 2 + 1, sizeof(t_intersec *));
	if (!ray_intersex)
		return (-1);
	for (int i = 0; objs[i]; i++)
	{
		arr_t = intersect(objs[i], ray);
		append_intersec(ray_intersex, arr_t, objs[i], i);
		free(arr_t);
	}
	for (int i = 0; ray_intersex[i]; i++)
	{
		printf("t: %f, obj: %s\n", ray_intersex[i]->t, ray_intersex[i]->object->id);
	}
	free(ray);
	for (int i = 0; ray_intersex[i]; i++)
		free(ray_intersex[i]);
	free(ray_intersex);
	free_objects(data, no_lines);
	for (int i = 0; objs[i]; i++)
		free(objs[i]);
	free(objs);
}