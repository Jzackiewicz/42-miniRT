/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:02:41 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/04 12:51:46 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(int ac, char **av)
{
	// prepare_window();
	(void) av;
	(void) ac;
	validate_file("src/testfile.rt");
	printf("file OK\n");
	return (0);
}