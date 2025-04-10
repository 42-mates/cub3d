/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:40:13 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/10 22:54:01 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    pad_lines(t_game *cub)
{
    int width = cub->map.width;
    int x, y;

    y = 0;
    while (y < cub->map.height)
    {
        x = 0;
        while (cub->map.grid[y][x])
            x++;
        while (x < width)
        {
            cub->map.grid[y][x] = ' ';
            x++;
        }
        y++;
    }
}

void    save_map_to_grid(t_map_node *lines, t_game *cub)
{
    t_map_node  *current;
    int         height;
    int         max_width;
    int         i;
    
    current = lines;
    height = 0;
    max_width = 0;
    while (current)
    {
        height++;
        if ((int)ft_strlen(current->line) > max_width)
            max_width = ft_strlen(current->line);
        current = current->next;
    }
    cub->map.grid = malloc(sizeof(char*) * (height + 1));
    if (!cub->map.grid)
    {
        printf("malloc fail\n");
        exit(1);
    }
    current = lines;
    i = 0;
    while (i < height)
    {
        cub->map.grid[i] = ft_strdup(current->line);
        current = current->next;
        i++;
    }
    cub->map.grid[height] = NULL;
    cub->map.height = height;
    cub->map.width = max_width;
    pad_lines(cub);
    deallocate_linked_list(cub->map.temp_list);
}


