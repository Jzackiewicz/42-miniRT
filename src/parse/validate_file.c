/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:01:40 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/04 11:59:12 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

// returns -1 on error, 0 on cool name d-_-b
int	check_extension(char *filepath)
{
	int	len;

	if (!filepath)
		return (-1);
	len = ft_strlen(filepath);
	if (len < 4)
		return (-1);
	if (*filepath == '.')
		filepath++;
	while (*filepath)
	{
		if (!ft_strncmp(filepath, ".rt\0", 4))
			return (0);
		else if (*filepath == '.' && ft_strncmp(filepath, ".rt\0", 4))
			return (-1);
		filepath++;
	}
	return (-1);
}

// exit(1) on file error
// TODO: no repeats on letter presence
void	validate_file(char *filepath)
{
	char	*line;
	char	**line_split;
	int		fd;

	line = NULL;
	if (check_extension(filepath) == -1)
		exit(1);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		exit(1);
	while (1)
	{
		line = get_next_line(fd);
		line_split = ft_split(line, ' ');
		if (!ft_strncmp(line_split[0], "A\0", 2))
			validate_ambient(line_split, line);
		else if (!ft_strncmp(line_split[0], "C\0", 2))
			validate_camera(line_split, line);
		else if (!ft_strncmp(line_split[0], "L\0", 2))
			validate_light(line_split, line);
		else if (!ft_strncmp(line_split[0], "S\0", 2))
			validate_sphere(line_split, line);
		else if (!ft_strncmp(line_split[0], "P\0", 2))
			validate_plane(line_split, line);
		else if (!ft_strncmp(line_split[0], "C\0", 2))
			validate_cylinder(line_split[0], line);
		else
			exit(1);
		ft_arr2d_free(line_split);
		free(line);
	}
}
