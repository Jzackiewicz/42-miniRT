/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:44:57 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/10 14:59:38 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void get_no_elements(char *filepath)
{
    char *line;
    char **line_split;
    int fd;
    int no_elems;
    
    no_elems = 0;
    fd = open(filepath, O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            return ;
        line_split = ft_split(line, ' ');
        free(line);
    }
}

// read line by line
// parse the lines according to the id with split, its already validated
// return the array of the objects/ settings
void parse_file(char *filepath)
{
    char *line;
    int fd;
    t_object *objects;
    
    if (validate_file(filepath) != 0)
        return ;
    fd = open(filepath, O_RDONLY);
    while (1)
    {
        
    }
}