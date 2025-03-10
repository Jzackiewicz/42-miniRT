/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:44:57 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/10 19:42:55 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	get_no_elements(char *filepath, int reset_flag)
{
	char	*line;
	char	**line_split;
	int		fd;
	int		no_elems;

	no_elems = 0;
	fd = open(filepath, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd, reset_flag);
		reset_flag = 0;
		if (!line)
			return (close(fd), no_elems);
		line_split = ft_split(line, ' ');
		free(line);
		if (!line_split || !*line_split)
			return (close(fd), -1);
		no_elems++;
		ft_arr2d_free(line_split);
	}
	return (close(fd), no_elems);
}

void	parse_element(char **line_split, t_object **objects, int i)
{
	if (!ft_strncmp(line_split[0], "A\0", 2) || !ft_strncmp(line_split[0],
			"C\0", 2) || !ft_strncmp(line_split[0], "L\0", 2))
		parse_settings(line_split, objects, i);
	else if (!ft_strncmp(line_split[0], "sp\0", 3) || !ft_strncmp(line_split[0],
			"pl\0", 3) || !ft_strncmp(line_split[0], "cy\0", 3))
		// tmp
		objects[i] = NULL;
}

int	parse_lines(int fd, char *line, char **line_split, t_object **objects)
{
	int	i;
	int	reset_flag;

	i = 0;
	reset_flag = 1;
	while (1)
	{
		line = get_next_line(fd, reset_flag);
		reset_flag = 0;
		if (!line)
			return (close(fd), 0);
		line_split = ft_split(line, ' ');
		free(line);
		if (!line_split)
			return (close(fd), -1);
		parse_element(line_split, objects, i);
		ft_arr2d_free(line_split);
		if (!objects[i])
			return (close(fd), -1);
		i++;
	}
	close(fd);
	return (0);
}

// TODO:
// object parsing
// get_next_line remains leaking()
// testing !!!
// memory testing !!!
void	parse_file(char *filepath)
{
	char		*line;
	char		**line_split;
	int			fd;
	int			no_elems;
	t_object	**objects;

	line = NULL;
	line_split = NULL;
	if (validate_file(filepath) != 0)
		return ;
	no_elems = get_no_elements(filepath, 1);
	objects = malloc((no_elems + 1) * sizeof(t_object *));
	if (!objects)
		return ;
	fd = open(filepath, O_RDONLY);
	parse_lines(fd, line, line_split, objects);
	for (int i = 0; i < 3; i++)
	{
		printf("\n");
		print_object(objects[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		free_object(objects[i]);
		free(objects[i]);
	}
	free(objects);
}
