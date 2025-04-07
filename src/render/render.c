/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 02:01:16 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/07 22:36:14 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_image *img, int x, int y, int color)
{
	int	offset;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		offset = (x * img->bits_per_pixel / 8) + (y * img->line_length);
		*(int *)(img->addr + offset) = color;
	}
}

// temp function to draw player
/*
void	player(t_image *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	for (j = 0; j < size; j++)
	{
		for (i = 0; i < size; i++)
		{
			put_pixel(img, x + i, y + j, color);
		}
	}
} */

static void	draw_background(t_game *cub)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		if (i < WIN_HEIGHT / 2)
			color = cub->map.ceiling_rgb;
		else
			color = cub->map.floor_rgb;
		while (j < WIN_WIDTH)
		{
			put_pixel(&cub->image, j, i, color);
			j++;
		}
		i++;
	}
}

// NOTE : floor & ceiling hardcoded, delete after parsing
void	render_frame(t_game *game)
{
	game->map.floor_rgb = 0x7be651;
	game->map.ceiling_rgb = 0x87CEEB;
	draw_background(game);
	/*	int y;	
		int x;
		y = 0;
		while (y < WIN_HEIGHT)
		{
			x = 0;
			while (x < WIN_WIDTH)
			{
				put_pixel(&game->image, x, y, 0x5e5b76);
				x++;
			}
			y++;
		} */
	if (game->minimap)
		draw_minimap(game, 4);
	// player(&game->image, game->player.pos_x, game->player.pos_y, 8, 0xFF0000);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
}
