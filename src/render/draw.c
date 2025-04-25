/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:38:08 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/26 01:30:05 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO : draw textures
// void	draw_wall_slice(t_game *cub, int x, double dist, int side)
// {
// 	int	line_height;
// 	int	start;
// 	int	end;
// 	int	y;
// 	int	color;

// 	if (dist <= 0.01)
// 		dist = 0.01;
// 	line_height = WIN_HEIGHT / dist;
// 	start = -line_height / 2 + WIN_HEIGHT / 2;
// 	if (start < 0)
// 		start = 0;
// 	end = line_height / 2 + WIN_HEIGHT / 2;
// 	if (end >= WIN_HEIGHT)
// 		end = WIN_HEIGHT - 1;
// 	if (side == 0)
// 		color = 0xAAAAAA;
// 	else
// 		color = 0x777777;
// 	y = start;
// 	while (y <= end)
// 	{
// 		put_pixel(&cub->image, x, y, color);
// 		y++;
// 	}
// }

static int	clamp_int(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

static double	clamp_double(double v, double min)
{
	if (v < min)
		return (min);
	return (v);
}

static int	get_tex_x(t_ray *ray, t_image *wall, t_player *player)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = player->pos_y + ray->wall_dist * ray->dir_y;
	else
		wall_x = player->pos_x + ray->wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * wall->w);
	if (ray->side == 0 && ray->dir_x < 0)
	    tex_x = wall->w - tex_x - 1;
	if (ray->side == 1 && ray->dir_y > 0)
	    tex_x = wall->w - tex_x - 1;
	tex_x = clamp_int(tex_x, 0, wall->w - 1);
	return (tex_x);
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

static void	draw_column(t_game *g, t_image *wall,
						int x, int start, int end, int tex_x, int line_h)
{
	int		y;
	int		d;
	int		tex_y;
	int		bpp;
	char	*src;
	int		color;

	bpp = wall->bpp / 8;
	y = start;
	while (y <= end)
	{
		d = y * 256 - WIN_HEIGHT * 128 + line_h * 128;
		tex_y = (d * wall->h) / line_h;
		tex_y = tex_y / 256;
		tex_y = clamp_int(tex_y, 0, wall->h - 1);
		src = wall->addr + tex_y * wall->line_len + tex_x * bpp;
		color = *(int *)src;
		put_pixel(&g->image, x, y, color);
		y++;
	}
}

// static void	draw_column(t_game *g, int x, int start, int end,
// 										int tex_x, int line_h)
// {
// 	int	y;
// 	int	d;
// 	int	tex_y;
// 	int	bpp;
// 	char	*src;
// 	int	color;

// 	bpp = g->wall.img.bits_per_pixel / 8;
// 	y = start;
// 	while (y <= end)
// 	{
// 		d = y * 256 - WIN_HEIGHT * 128 + line_h * 128;
// 		tex_y = (d * g->wall.h) / line_h;
// 		tex_y = tex_y / 256;
// 		tex_y = clamp_int(tex_y, 0, g->wall.h - 1);
// 		src = g->wall.img.addr + tex_y * g->wall.img.line_length + tex_x * bpp;
// 		color = *(int *)src;
// 		put_pixel(&g->image, x, y, color);
// 		y++;
// 	}
// }

static t_image *get_tex(t_game *g, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->map_x > g->player.pos_x)
			return (g->tex.ea);
		else
			return (g->tex.we);
	}
	else
	{
		if (ray->map_y > g->player.pos_y)
			return (g->tex.so);
		else
			return (g->tex.no);
	}
}

void	draw_wall(t_game *g, t_ray *ray, int x)
{
	int		line_h;
	int		start;
	int		end;
	int		tex_x;
	double	dist;
	t_image	*wall;

	dist = clamp_double(ray->wall_dist, 0.01);
	line_h = (int)(WIN_HEIGHT / dist);
	get_line_limits(&start, &end, line_h);
	wall = get_tex(g, ray);
	tex_x = get_tex_x(ray, wall, &g->player);
	draw_column(g, wall, x, start, end, tex_x, line_h);
	// tex_x = get_tex_x(g, ray);
	// draw_column(g, x, start, end, tex_x, line_h);
}

// void draw_wall_slice(t_game *cub, t_ray *ray, int x)
// {
// 	int line_h;
// 	int start;
// 	int end;
	
// 	line_h = WIN_HEIGHT / ray->wall_dist;
// 	start = -line_h / 2 + WIN_HEIGHT / 2;
// 	if (start < 0)
// 		start = 0;
// 	end = line_h / 2 + WIN_HEIGHT / 2;
// 	if (end >= WIN_HEIGHT)
// 		end = WIN_HEIGHT - 1;

// 	/* --- 1. где попали в стену --- */
// 	double wallX;

// 	if (ray->side == 0)
// 		wallX = cub->player.pos_y + ray->wall_dist * ray->dir_y;
// 	else
// 		wallX = cub->player.pos_x + ray->wall_dist * ray->dir_x;
// 	wallX -= floor(wallX);

// 	/* --- 2. горизонтальная координата в текстуре --- */
// 	int texX = (int)(wallX * cub->wall.w);

// 	/* --- 3. идём по каждому y экрана, берём соответствующий texY --- */
// 	for (int y = start; y <= end; ++y)
// 	{
// 		int d = (y * 256 - WIN_HEIGHT * 128 + line_h * 128);
// 		int texY  = ((d * cub->wall.h) / line_h) / 256;
// 		if (texX < 0) texX = 0;
// 		if (texX >= cub->wall.w)
// 			texX = cub->wall.w - 1;
// 		if (texY < 0)
// 			texY = 0;
// 		if (texY >= cub->wall.h)
// 			texY = cub->wall.h - 1;

// 		char *src = cub->wall.img.addr
// 				  + texY * cub->wall.img.line_length
// 				  + texX * (cub->wall.img.bits_per_pixel / 8);
// 		int color = *(int *)src;
// 		put_pixel(&cub->image, x, y, color);
// 	}
// }
