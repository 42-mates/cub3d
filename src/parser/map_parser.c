/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:13:57 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/05 17:06:17 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void    convert_rgb_to_hex(char *s)
// {
    
// }

void	purge_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void    print_temp_list(t_temp_map *map)
{
    t_map_node  *current = map->top;

    while (current)
    {
        printf("%s", current->line);
        current = current->next;
    }
}

void    map_list_append(char *line, t_temp_map *map_list)
{
    t_map_node  *current;
    t_map_node  *new_node = malloc(sizeof(t_map_node));
    if (!new_node)
    {
        printf("malloc failed\n");
        exit(1);
    }
    new_node->line = ft_strdup(line);
    new_node->next = NULL;
    map_list->height++;
    if (!map_list->top)
    {
        map_list->top = new_node;
        return ;
    }
    current = map_list->top;
    while (current->next)
        current = current->next;
    current->next = new_node;
}

void    extract_line(char *line, t_game *cub, t_temp_map *map_list)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
        cub->map.no_texture = line;
    else if (ft_strncmp(line, "SO ", 3) == 0)
        cub->map.so_texture = line;
    else if (ft_strncmp(line, "WE ", 3) == 0)
        cub->map.we_texture = line;
    else if (ft_strncmp(line, "EA ", 3) == 0)
        cub->map.ea_texture = line;
    // else if (ft_strncmp(line, "F ", 2) == 0)
    //     cub->map.floor_rgb = line;
    // else if (ft_strncmp(line, "C ", 2) == 0)
    //     cub->map.ceiling_rgb = line;
    else
    {
        map_list_append(line, map_list);
    }
}

t_temp_map  *create_temp_map(void)
{
    t_temp_map  *map;
    
    map = malloc(sizeof(t_temp_map));
    if (!map)
    {
        printf("Error: malloc\n");
        exit(1);
    }
    map->height = 0;
    map->top = NULL;
    return (map);
}

void    save_map_to_grid(t_temp_map *map, t_game *cub)
{
    t_map_node  *current = map->top;

    cub->map.grid = malloc(sizeof(char*) * map->height);
    if (!cub->map.grid)
    {
        printf("malloc fail\n");
        exit(1);
    }
    int i = 0;
    while (i < (int)map->height)
    {
        cub->map.grid[i] = ft_strdup(current->line);
        current = current->next;
        i++;
    }
}

void    extract_map(char *file_name, t_game *cub)
{
    int     fd;
    char    *line;
    t_temp_map  *map;
    
    map = create_temp_map();
    // add: error handling for temp map
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
    {
        printf("Error: failed to open file\n");
        exit(1);
    }
    line = get_next_line(fd);
    if (line == NULL)
    {
        printf("Error: empty file\n");
        exit(1);
    }
    while (line != NULL)
    {
        // if (ft_strlen(line) == 1 && ft_strncmp(line, "\n", 1) == 0)
        //     line = get_next_line(fd);
        // else
        // {
            extract_line(line, cub, map);
            line = get_next_line(fd);
        // }
    }
    printf("map height = %d\n", map->height);
    print_temp_list(map);
    save_map_to_grid(map, cub);
    close(fd);
}
