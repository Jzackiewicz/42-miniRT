/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:01:40 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/04 15:25:44 by agarbacz         ###   ########.fr       */
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

int drain_file(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (-1);
		free(line);
	}
	close(fd);
	return (-1);
}

// exit(1) on file error
// TODO: no repeats on letter presence
// refactor
int	validate_file(char *filepath)
{
	char	*line;
	char	**line_split;
	int		fd;
	int		setting_status, objects_status;

	line = NULL;
	if (check_extension(filepath) == -1)
		exit(1);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		exit(1);
	while (1)
	{
		line = get_next_line(fd);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (line)
		{
			line_split = ft_split(line, ' ');
			free(line);
		}
		else
			break ;
		setting_status = validate_settings(line_split, fd);
		if (setting_status == -1)
			return (-1);
		objects_status = validate_objects(line_split, fd);
		if (objects_status == -1)
			return (-1);
		if (setting_status == 1 && objects_status == 1)
			return (drain_file(fd));
		ft_arr2d_free(line_split);
	}
	close(fd);
	return (0);
}
