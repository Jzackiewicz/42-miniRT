/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:28:39 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/03 10:28:42 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(void)
{
	t_input_data	**input_data;
	t_world			*world_data;
	int				**bitmap;
	int				no_lines;

	input_data = NULL;
	no_lines = parse_file("tests/integration_tests/testfiles/valid_nocy.rt",
			&input_data);
	if (no_lines == -1)
		return (printf("Error: file error\n"), -1);
	world_data = create_world(input_data, no_lines);
	free_input_data(input_data, no_lines);
	bitmap = generate_bitmap(world_data);
	free_world(world_data);
	mlx_run(bitmap);
	return (0);
}
