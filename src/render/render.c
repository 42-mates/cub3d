/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 02:01:16 by oprosvir          #+#    #+#             */
/*   Updated: 2024/12/25 20:28:10 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel(t_image *img, int x, int y, int color)
{
	int	offset;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		offset = (x * img->bits_per_pixel / 8) + (y * img->line_length);
		*(int *)(img->addr + offset) = color;
	}
}

// temp function to draw player
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
}

void	render_frame(t_game *game)
{
	int x;
	int y;

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
	}
	player(&game->image, game->player.pos_x, game->player.pos_y, 20, 0xFF0000);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
}