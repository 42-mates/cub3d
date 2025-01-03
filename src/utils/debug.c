/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:50:55 by oprosvir          #+#    #+#             */
/*   Updated: 2024/12/29 20:00:07 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_image_data(const t_image *image)
{
	printf("Image Data:\n");
	printf("  img: %p\n", image->img);
	printf("  addr: %p\n", image->addr);
	printf("  bits_per_pixel: %d\n", image->bits_per_pixel);
	printf("  line_length: %d\n", image->line_length);
	printf("  endian: %d\n", image->endian);
	printf("\n");
}

void	print_player_data(const t_player *player)
{
	printf("Player Data:\n");
	printf("  pos_x: %d\n", player->pos_x);
	printf("  pos_y: %d\n", player->pos_y);
	printf("\n");
}

void print_map_data(const t_map *map)
{
	int i;

	printf("Map Data:\n");
	printf("  width: %d\n", map->width);
	printf("  height: %d\n", map->height);
	printf("  grid:\n");
	if (map->grid)
	{
		for (i = 0; i < map->height; i++)
		{
			printf("    %s\n", map->grid[i]);
		}
	}
	else
		printf("    (null)\n");
	printf("  north_texture: %s\n", map->no_texture ? map->no_texture : "(null)");
	printf("  south_texture: %s\n", map->so_texture ? map->so_texture : "(null)");
	printf("  west_texture: %s\n", map->we_texture ? map->we_texture : "(null)");
	printf("  east_texture: %s\n", map->ea_texture ? map->ea_texture : "(null)");
	printf("  floor_rgb: %d\n", map->floor_rgb);
	printf("  ceiling_rgb: %d\n", map->ceiling_rgb);
	printf("\n");
}

void print_data(const t_game *cub)
{
	printf("Game Data:\n");
	printf("  mlx: %p\n", cub->mlx);
	printf("  win: %p\n\n", cub->win);
	print_image_data(&cub->image);
	print_player_data(&cub->player);
	print_map_data(&cub->map);
}
