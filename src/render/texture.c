/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 23:51:20 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/26 00:06:37 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_image *load_texture(t_game *cub, char *path)
{
	t_image *tex;

	tex = malloc(sizeof(t_image));
	if (!tex)
		error_exit(cub, "Malloc failed in load_texture");
	tex->img = mlx_xpm_file_to_image(cub->mlx, path, &tex->w, &tex->h);
	if (!tex->img)
		error_exit(cub, "Failed to load texture");
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->addr)
		error_exit(cub, "Failed to get texture data address");
	return (tex);
}

void load_textures(t_game *cub)
{
	cub->tex.no = load_texture(cub, cub->map.no_texture);
	cub->tex.so = load_texture(cub, cub->map.so_texture);
	cub->tex.we = load_texture(cub, cub->map.we_texture);
	cub->tex.ea = load_texture(cub, cub->map.ea_texture);
}
