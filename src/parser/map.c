/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:40:13 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/10 00:43:48 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    save_map_to_grid(t_map_node *lines, t_game *cub)
{
    t_map_node  *current;
    int         height;
    int         i;
    
    current = lines;
    height = 0;
    while (current)
    {
        height++;
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
}

void    map_list_append(char *line, t_map_node **map_line)
{
    t_map_node  *current;
    t_map_node  *new_node;
    
    new_node = malloc(sizeof(t_map_node));
    if (!new_node)
    {
        printf("malloc failed\n");
        exit(1);
    }
    new_node->line = ft_strdup(line);
    new_node->next = NULL;
    if (*map_line == NULL)
    {
        *map_line = new_node;
        return ;
    }
    current = *map_line;
    while (current->next)
        current = current->next;
    current->next = new_node;
}
