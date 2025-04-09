/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:13:57 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/10 00:33:26 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_args(int argc, char **argv)
{
	char	*s;
	int		fd;

	if (argc != 2)
		exit_failure("Invalid number of arguments");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
	{
		close(fd);
		exit_failure("File does not exist or is a directory");
	}
	close(fd);
	s = ft_strchr(argv[1], '.');
	if (s)
	{
		if (ft_strcmp(s, ".cub") == 0 && ft_strlen(s) == 4)
			return ;
	}
	exit_failure("Invalid file format");
}

int line_is_empty(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ')
            return (1);
        i++;
    }
    return (0);
}

int is_map_line(char *line)
{
    char    *trimmed;
    int     is_map_line;

    is_map_line = 0;
    trimmed = ft_strtrim(line, " ");
    if (trimmed[0] == '0' || trimmed[0] == '1')
        is_map_line = 1;
    free(trimmed);
    return (is_map_line);
}

void    deallocate_linked_list(t_map_node *map_lines)
{
    t_map_node  *current;
    t_map_node  *tmp;

    current = map_lines;
    while (current)
    {
        tmp = current;
        current = current->next;
        free(tmp);
    }
}

void    parse_scene_file(char *file_name, t_game *cub)
{
    int         fd;
    char        *line;
    t_map_node  *map_lines;
    
    map_lines = NULL;
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        exit_failure("File can't be opened");
    line = get_next_line(fd);
    if (line == NULL)
    {
        close(fd);
        exit_failure("Empty file");
    }
    while (line != NULL)
    {
        if (is_config_line(line))
            parse_config(line, cub);
        else if (is_map_line(line))
            map_list_append(line, &map_lines);
        else if (!line_is_empty(line))
        {
            // handle memory leaks
            close(fd);
            exit_failure("Invalid line in .cub file");
        }
        line = get_next_line(fd);
    }
    print_temp_list(map_lines);
    save_map_to_grid(map_lines, cub);
    close(fd);
}
