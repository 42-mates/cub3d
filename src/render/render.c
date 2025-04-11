/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 02:01:16 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/11 13:41:57 by mglikenf         ###   ########.fr       */
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
	//game->map.floor_rgb = 0x7be651;
	//game->map.ceiling_rgb = 0x87CEEB;
	draw_background(game);
	if (game->minimap)
		draw_minimap(game, 4);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
}
