/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:44:45 by oprosvir          #+#    #+#             */
/*   Updated: 2025/01/03 21:15:18 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_window(t_game *cub, char *title)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		allocation_error(cub, "Error: Unable to initialize MLX");
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, title);
	if (!cub->win)
		allocation_error(cub, "Error: Unable to create window");
	cub->image.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->image.img)
		allocation_error(cub, "Error: Unable to create image");
	cub->image.addr = mlx_get_data_addr(cub->image.img,
			&cub->image.bits_per_pixel, &cub->image.line_length,
			&cub->image.endian);
	if (!cub->image.addr)
		allocation_error(cub, "Error: Unable to get image data address");
}

// NOTE : player position init temp, set to '-1' before parsing
t_game	init_game(void)
{
	t_game	cub;

	ft_bzero(&cub, sizeof(t_game));
	init_window(&cub, WIN_TITLE);
	cub.player.pos_x = WIN_WIDTH / 2;
	cub.player.pos_y = WIN_HEIGHT / 2;
	cub.map.width = -1;
	cub.map.height = -1;
	cub.map.floor_rgb = -1;
	cub.map.ceiling_rgb = -1;
    cub.minimap = 1;
	return (cub);
}
