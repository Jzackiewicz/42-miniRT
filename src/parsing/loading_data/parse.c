/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:44:57 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/14 12:09:31 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/parser.h"

/* counts the number of objects / settings in the file
neccessary for proper memory allocation and deallocation */
int	get_no_elements(char *filepath)
{
	char	*line;
	char	**line_split;
	int		fd;
	int		no_elems;

	no_elems = 0;
	fd = open(filepath, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (free(line), close(fd), no_elems);
		line_split = ft_split(line, ' ');
		free(line);
		if (!line_split || !*line_split)
			return (close(fd), -1);
		if (line_split[0][0] != '\n')
			no_elems++;
		ft_arr2d_free(line_split);
	}
	return (close(fd), no_elems);
}

void	parse_element(char **line_split, t_input_data **objects, int i)
{
	if (!ft_strncmp(line_split[0], "A\0", 2) || !ft_strncmp(line_split[0],
			"C\0", 2) || !ft_strncmp(line_split[0], "L\0", 2))
		parse_settings(line_split, objects, i);
	else if (!ft_strncmp(line_split[0], "sp\0", 3) || !ft_strncmp(line_split[0],
			"pl\0", 3) || !ft_strncmp(line_split[0], "cy\0", 3))
		parse_objects(line_split, objects, i);
}

int	parse_lines(int fd, char *line, char **line_split, t_input_data **objects)
{
	int	i;

	i = -1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (close(fd), 0);
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		line_split = ft_split(line, ' ');
		free(line);
		if (!line_split)
			return (close(fd), -1);
		parse_element(line_split, objects, ++i);
		ft_arr2d_free(line_split);
		if (!objects[i])
			return (close(fd), -1);
	}
	close(fd);
	return (0);
}

/* returns the number of parsed elements which are passed
 	by the caller to the free_objects() funcs
 	-1 on error */
int	parse_file(char *filepath, t_input_data ***objects)
{
	char	*line;
	char	**line_split;
	int		fd;
	int		no_elems;

	line = NULL;
	line_split = NULL;
	if (validate_file(filepath) != 0)
		return (-1);
	no_elems = get_no_elements(filepath);
	*objects = (t_input_data **)malloc((no_elems + 1) * sizeof(t_input_data *));
	if (!*objects)
		return (-1);
	fd = open(filepath, O_RDONLY);
	parse_lines(fd, line, line_split, *objects);
	return (no_elems);
}
