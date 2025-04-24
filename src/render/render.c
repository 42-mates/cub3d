/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 02:01:16 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/24 17:55:38 by oprosvir         ###   ########.fr       */
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

static void put_text(t_game *cub, char *text, int *y)
{
	int	x0;
	
	x0 = WIN_WIDTH - 220;
	mlx_string_put(cub->mlx, cub->win, x0 + 1, *y + 1, BLACK, text);
	mlx_string_put(cub->mlx, cub->win, x0, *y, WHITE, text);
	*y += 15;
}

static void draw_controls(t_game *cub)
{
	int	y;
	
	y = 20;
	put_text(cub, "         CONTROLS", &y);
	put_text(cub, " ", &y);
	put_text(cub, "Move        W A S D", &y);
	put_text(cub, "Rotate      < / >", &y);
	put_text(cub, "            Mouse (click & drag)", &y);
	put_text(cub, "Minimap     M     toggle", &y);
	put_text(cub, "            + / - resize", &y);
	put_text(cub, "Controls    C     toggle", &y);
	put_text(cub, "Quit        ESC", &y);
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

void	render_frame(t_game *cub)
{
	draw_background(cub);
	render_rays(cub);
	if (cub->minimap)
		draw_minimap(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->image.img, 0, 0);
	if (cub->controls)
		draw_controls(cub);
}
