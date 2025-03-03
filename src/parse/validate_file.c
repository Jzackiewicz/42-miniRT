/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:01:40 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/03 12:05:31 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

// returns -1 on error, 0 on cool name d-_-b
int check_extension(char *filepath)
{
    int len;

	len = ft_strlen(filepath);
	if (len < 4)
		return (-1);
	while (*filepath)
	{
		if (ft_strncmp(filepath, ".rt", 3))
			return (0);
		filepath++;
	}
	return (-1);
}
