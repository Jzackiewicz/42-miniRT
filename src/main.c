/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:28:39 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/29 11:35:01 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(int ac, char **av)
{
	t_input_data	**input_data;
	t_world			*world_data;
	int				no_lines;

	if (ac != 2)
	{
		printf("Error!\nValid execution: ./miniRT <relative-path-to-scene.rt>\n");
		return (-1);
	}
	input_data = NULL;
	no_lines = parse_file(av[1], &input_data);
	if (no_lines == -1)
		return (printf("Error: file error\n"), -1);
	world_data = create_world(input_data);
	mlx_run(world_data, no_lines, input_data);
	return (0);
}
