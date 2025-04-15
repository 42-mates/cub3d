/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 02:01:16 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/15 20:45:31 by oprosvir         ###   ########.fr       */
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

static void	render_rays(t_game *cub)
{
	int		x;
	t_ray	ray;
	double	camera_x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
		ft_bzero(&ray, sizeof(t_ray));
		cast_ray(cub, &ray, camera_x);
		draw_wall_slice(cub, x, ray.wall_dist, ray.side);
		x++;
	}
}

void	render_frame(t_game *cub)
{
	draw_background(cub);
	render_rays(cub);
	if (cub->minimap)
		draw_minimap(cub, 8);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->image.img, 0, 0);
}
