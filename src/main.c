/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:02:41 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/11 15:12:11 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// no_objects variable is neccessary for properly freeing the objects
int	main(int ac, char **av)
{
	t_object	**objs;
	int			no_objects;

	(void)ac;
	(void)av;
	objs = NULL;
	no_objects = parse_file("tests/integration_tests/testfiles/valid.rt",
			&objs);
	free_objects(objs, no_objects);
	return (0);
}
