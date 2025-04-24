/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:40:13 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/25 01:01:00 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    calculate_grid_dimensions(t_game *cub)
{
    t_map_node  *current;
    int         max_width;
    int         height;

    current = cub->map.temp_list;
    max_width = 0;
    height = 0;
    while (current)
    {
        height++;
        if ((int)ft_strlen(current->line) > max_width)
            max_width = ft_strlen(current->line);
        current = current->next;
    }
    cub->map.height = height;
    cub->map.width = max_width;
}

// @mglikenf    check in save_map_to_grid
void	check_map_size(t_game *cub, int w, int h)
{
	if (w > MAX_MAP_W || h > MAX_MAP_H)
		error_exit(cub, "Map too big (max 70x70)");
}

void    fill_and_pad_grid_lines(t_game *cub)
{
    t_map_node  *current;
    int         i;
    int         line_len;

    i = 0;
    current = cub->map.temp_list;
    while (i < cub->map.height && current)
    {
        cub->map.grid[i] = malloc((cub->map.width + 1));
        if (!cub->map.grid[i])
        {
            free_memory_and_exit(cub);
            exit_failure("malloc fail");
        }
        line_len = ft_strlen(current->line);
        ft_memset(cub->map.grid[i], ' ', cub->map.width);
        ft_memcpy(cub->map.grid[i], current->line, line_len);
        cub->map.grid[i][cub->map.width] = '\0';
        current = current->next;
        i++;
    }
}

void    save_map_to_grid(t_game *cub)
{
    calculate_grid_dimensions(cub);
    cub->map.grid = malloc(sizeof(char*) * (cub->map.height + 1));
    if (!cub->map.grid)
    {
        printf("malloc fail\n");
        free_memory_and_exit(cub);
        exit(1);
    }
    fill_and_pad_grid_lines(cub);
    cub->map.grid[cub->map.height] = NULL;
    deallocate_linked_list(cub->map.temp_list);
}

void    free_memory_and_exit(t_game *cub)
{
    int     i;
    t_map   map;

    map = cub->map;
    if (map.grid)
    {
        i = 0;
        while (map.grid[i])
        {
            free(map.grid[i]);
            i++;
        }
        free(map.grid);
    }
    free(map.no_texture);
    free(map.so_texture);
    free(map.ea_texture);
    free(map.we_texture);
    if (map.temp_list)
        deallocate_linked_list(map.temp_list);
}