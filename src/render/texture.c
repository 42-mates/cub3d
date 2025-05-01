/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 23:51:20 by oprosvir          #+#    #+#             */
/*   Updated: 2025/05/01 20:51:27 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tex_y(int y, int line_h, int tex_h)
{
	int	d;
	int	tex_y;

	d = y * 256 - WIN_HEIGHT * 128 + line_h * 128;
	tex_y = (d * tex_h) / line_h;
	tex_y = clamp_int(tex_y / 256, 0, tex_h - 1);
	return (tex_y);
}

int	get_tex_x(t_ray *ray, t_image *wall, t_player *player)
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

void load_texture(t_game *cub, t_image *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx, path, &tex->w, &tex->h);
	if (!tex->img)
		error_exit(cub, "Texture load failed");
	if (tex->w > MAX_TEX || tex->h > MAX_TEX)
		error_exit(cub, "Texture too large (max 800x800)");
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->addr)
		error_exit(cub, "Get texture addr failed");
}

void	load_textures(t_game *cub)
{
	load_texture(cub, &cub->tex.no, cub->map.no_texture);
	load_texture(cub, &cub->tex.so, cub->map.so_texture);
	load_texture(cub, &cub->tex.we, cub->map.we_texture);
	load_texture(cub, &cub->tex.ea, cub->map.ea_texture);
}
