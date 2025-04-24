/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:06:32 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/24 18:32:23 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int append_players(char *line)
{
    char    *orientation_set = "NEWSnews";
    int     i;
    int     count;

    i = 0;
    count = 0;
    while (line[i])
    {
        if (ft_strchr(orientation_set, line[i]))
            count++;
        i++;
    }
    return (count);
}

int     line_has_invalid_chars(char *line)
{
    char    *valid_set;
    int     i;

    valid_set = "10 NEWSnews";
    i = 0;
    while (line[i])
    {
        if (!ft_strchr(valid_set, line[i]))
        {
            printf("line contains an invalid character = %c\n", line[i]);
            return (1);
        }
        i++;
    }
    return (0);
}

int validate_map_lines(t_map_node *head)
{
    t_map_node  *current;
    int         num_of_players;

    current = head;
    num_of_players = 0;
    while (current)
    {
        if (line_has_invalid_chars(current->line))
            return (1);
        num_of_players += append_players(current->line);
        current = current->next;
    }
    if (num_of_players != 1)
    {
        printf("no players at all or too many");
        return (1);
    }
    return (0);
}

int is_walkable_tile(char tile)
{
    char    *set;

    set = "NSWE0";
    if (ft_strchr(set, tile))
        return (1);
    return (0);
}

int has_invalid_neighbor(int y, int x, t_map *map)
{
    if (y == 0 || y >= map->height - 1 || x == 0 || x >= map->width - 1)
    {
        printf("tile (x=%d, y=%d) is located on edge of the map\n", x, y);
        return (1);
    }
    if (map->grid[y - 1][x] == ' ' || map->grid[y + 1][x] == ' ' || map->grid[y][x - 1] == ' ' || map->grid[y][x + 1] == ' ')
        return (printf("map has a hole\n"), 1);
    return (0);
}

void    validate_tiles(t_game *cub)
{
    int     y;
    int     x;
    char    tile;

    y = 0;
    while (y < cub->map.height)
    {
        x = 0;
        while (x < cub->map.width)
        {
            tile = cub->map.grid[y][x];
            if (is_walkable_tile(tile))
            {
                if (has_invalid_neighbor(y, x, &cub->map))
                {
                    free_memory_and_exit(cub);
                    printf("Error\nMap is invalid\n");
                    exit_code(cub, 1);
                }
            }
            x++;
        }
        y++;
    }
}

void	validate_map_content(t_game *cub)
{
	if (validate_map_lines(cub->map.temp_list))
    {
        printf("map is invalid\n");
        // cleanup and exit
    }
    save_map_to_grid(cub);
    validate_tiles(cub);
}
