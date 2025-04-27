/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:06:32 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/27 23:50:17 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int append_players(char *line)
{
    char    *orientation_set = "NEWS";
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

    valid_set = "10 NEWS";
    i = 0;
    while (line[i])
    {
        if (!ft_strchr(valid_set, line[i]))
            return (1);
        i++;
    }
    return (0);
}

void validate_map_lines(t_game *cub, t_map_node *head)
{
    t_map_node  *current;
    int         num_of_players;

    current = head;
    num_of_players = 0;
    while (current)
    {
        if (line_has_invalid_chars(current->line))
            error_exit(cub, "Invalid character in map");
        num_of_players += append_players(current->line);
        current = current->next;
    }
    if (num_of_players != 1)
        error_exit(cub, "Number of players must be exactly one");
}

int has_invalid_neighbor(int y, int x, t_map *map)
{
    if (y == 0 || y >= map->height - 1 || x == 0 || x >= map->width - 1)
    {
        printf("tile (x=%d, y=%d) is located on edge of the map\n", x, y);
        return (1);
    }
    if (map->grid[y - 1][x] == ' ' || map->grid[y + 1][x] == ' ' || map->grid[y][x - 1] == ' ' || map->grid[y][x + 1] == ' ')
        return (1);
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
            if (ft_strchr("NEWS0", tile))
            {
                if (has_invalid_neighbor(y, x, &cub->map))
                    error_exit(cub, "Map is invalid");
            }
            x++;
        }
        y++;
    }
}
