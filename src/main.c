/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:02:41 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/14 12:12:42 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// TODO:	properly analyze and test the intersection calculations
//			differenct struct for objects and settings


//Parsing:
//			czemu objects to trójwymiarowa tablica, skoro potem jedyne odwołanie do niej jest przez dereferencję
//			może dać ft_calloc i nie zbierać no_lines?

int main()
{
	t_ray *ray;
	double o[] = {30.0, 0.0, 30.0, 1.0};
	double d[] = {1.0, 0.0, 0.0, 0.0};
	// double	*arr_t;
	t_input_data	**data;
	t_object		**objs;
	t_intersec	*ray_intersex;
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
	ray_intersex = (t_intersec *)ft_calloc(no_lines - 3 + 1, sizeof(t_intersec));
	if (!ray_intersex)
		return (-1);
	// for (int i = 0; objs[i]; i++)
	// {
	// 	arr_t = intersect(objs[i], ray);
	// 	append_intersec(&ray_intersex, arr_t, objs[i], i);
	// 	//free(arr_t);
	// }
	
	// for (int i = 0; objs[i]; i++)
	// {
	// 	printf("main: %f\n", ray_intersex[i].t);
	// }
	free(ray);
	free(ray_intersex);
	free_objects(data, no_lines);
	for (int i = 0; objs[i]; i++)
		free(objs[i]);
	free(objs);
}