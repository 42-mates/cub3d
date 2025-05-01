/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:38:08 by oprosvir          #+#    #+#             */
/*   Updated: 2025/05/01 20:32:20 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	clamp_int(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

static void	get_line_limits(int *start, int *end, int line_h)
{
	*start = WIN_HEIGHT / 2 - line_h / 2;
	if (*start < 0)
		*start = 0;
	*end = WIN_HEIGHT / 2 + line_h / 2;
	if (*end >= WIN_HEIGHT)
		*end = WIN_HEIGHT - 1;
}

static int	get_pixel_color(t_image *wall, int tex_x, int tex_y)
{
	int		bpp;
	char	*src;

	bpp = wall->bpp / 8;
	src = wall->addr + tex_y * wall->line_len + tex_x * bpp;
	return (*(int *)src);
}

static void	draw_column(t_game *g, t_image *wall, int x, int line_h)
{
	int	start;
	int	end;
	int	tex_x;
	int	tex_y;
	int	color;

	get_line_limits(&start, &end, line_h);
	tex_x = get_tex_x(&g->ray, wall, &g->player);
	while (start <= end)
	{
		tex_y = get_tex_y(start, line_h, wall->h);
		color = get_pixel_color(wall, tex_x, tex_y);
		put_pixel(&g->image, x, start, color);
		start++;
	}
}

void	draw_wall(t_game *g, int x)
{
	t_ray	*ray;
	int		line_h;

	ray = &g->ray;
	line_h = (int)(WIN_HEIGHT / ray->wall_dist);
	if (ray->side == 0)
	{
		if (ray->map_x > g->player.pos_x)
			draw_column(g, &g->tex.ea, x, line_h);
		else
			draw_column(g, &g->tex.we, x, line_h);
	}
	else
	{
		if (ray->map_y > g->player.pos_y)
			draw_column(g, &g->tex.so, x, line_h);
		else
			draw_column(g, &g->tex.no, x, line_h);
	}
}
