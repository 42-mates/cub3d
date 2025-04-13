/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:06:31 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/13 20:33:28 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_cell_color(t_game *game, int x, int y)
{
	char tile;
	
	tile = game->map.grid[y][x];	
	if (tile == '1')
		return (BLACK);
	if (tile == '0')
		return (WHITE);
	return (-1);
}

static void	draw_minimap_cell(t_game *game, int col, int row, int cell_size)
{
	int	color;
	int	i;
	int	j;

	color = get_cell_color(game, col, row);
	if (color == -1)
		return ;
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

static void	direction_line(t_game *game, int x, int y, int len)
{
	int	i;
	int	dx;
	int	dy;

	i = 0;
	while (i < len)
	{
		dx = (int)(game->player.dir_x * i);
		dy = (int)(game->player.dir_y * i);
		put_pixel(&game->image, x + dx, y + dy, 0xFF0000);
		i++;
	}
}

static void	draw_minimap_player(t_game *game, int cell_size)
{
	int	px;
	int	py;
	int	i;
	int	j;

	px = game->player.pos_x * cell_size;
	py = game->player.pos_y * cell_size;
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			put_pixel(&game->image, px + i, py + j, 0xFF0000);
			j++;
		}
		i++;
	}
	direction_line(game, px, py, cell_size);
}

// TODO : scrollable minimap, scale
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
	draw_minimap_player(game, cell_size);
}
