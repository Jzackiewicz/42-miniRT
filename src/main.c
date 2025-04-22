/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:28:39 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/22 14:35:14 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(void)
{
	t_input_data	**input_data;
	t_world			*world_data;
	int				no_lines;

	input_data = NULL;
	no_lines = parse_file("tests/integration_tests/testfiles/cylindron.rt",
			&input_data);
	if (no_lines == -1)
		return (printf("Error: file error\n"), -1);
	world_data = create_world(input_data);
	mlx_run(world_data, no_lines, input_data);
	return (0);
}
