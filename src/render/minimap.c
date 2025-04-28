/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:06:31 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/28 14:38:17 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	cell_color(t_game *cub, int x, int y)
{
	char	tile;

	tile = cub->map.grid[y][x];
	if (tile == '1')
		return (DARK_GREY);
	if (tile == '0')
		return (GREY);
	return (-1);
}

static void	draw_cell(t_game *cub, int x, int y, int scale)
{
	int	color;
	int	i;
	int	j;

	color = cell_color(cub, x, y);
	if (color == -1)
		return ;
	i = 0;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			put_pixel(&cub->image, x * scale + i, y * scale + j, color);
			j++;
		}
		i++;
	}
}

static void	dir_line(t_game *cub, int px, int py)
{
	int	i;
	int	dx;
	int	dy;

	i = 0;
	while (i < DIR_LEN)
	{
		dx = (int)(cub->player.dir_x * i);
		dy = (int)(cub->player.dir_y * i);
		put_pixel(&cub->image, px + dx, py + dy, RED);
		i++;
	}
}

static void	draw_player(t_game *cub, int scale)
{
	int	px;
	int	py;
	int	i;
	int	j;

	px = cub->player.pos_x * scale;
	py = cub->player.pos_y * scale;
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			put_pixel(&cub->image, px + i, py + j, RED);
			j++;
		}
		i++;
	}
	dir_line(cub, px, py);
}

void	draw_minimap(t_game *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub->map.height)
	{
		x = 0;
		while (x < cub->map.width)
		{
			draw_cell(cub, x, y, cub->map_scale);
			x++;
		}
		y++;
	}
	draw_player(cub, cub->map_scale);
}
