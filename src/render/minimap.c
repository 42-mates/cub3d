/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:06:31 by oprosvir          #+#    #+#             */
/*   Updated: 2025/01/03 21:55:26 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO : handle spaces in map
static int	get_cell_color(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == '1')
		return (0xFFFFFF);
	return (0x000000);
}

static void	draw_minimap_cell(t_game *game, int col, int row, int cell_size)
{
	int	color;
	int	i;
	int	j;

	color = get_cell_color(game, col, row);
	i = 0;
	while (i < cell_size)
	{
		j = 0;
		while (j < cell_size)
		{
			put_pixel(&game->image, col * cell_size + i, row * cell_size + j,
				color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_player(t_game *game, int map_scale)
{
	int	px;
	int	py;
	int	i;
	int	j;

	px = game->player.pos_x / map_scale;
	py = game->player.pos_y / map_scale;
	i = -2;
	while (i < 2)
	{
		j = -2;
		while (j < 2)
		{
			put_pixel(&game->image, px + i, py + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

// TODO : scrollable minimap, player position
void	draw_minimap(t_game *game, int map_scale)
{
	int	cell_size;
	int	x;
	int	y;

	cell_size = WIN_WIDTH / (game->map.width * map_scale);
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			draw_minimap_cell(game, x, y, cell_size);
			x++;
		}
		y++;
	}
	draw_minimap_player(game, map_scale);
}
