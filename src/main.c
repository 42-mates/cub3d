/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:42:38 by oprosvir          #+#    #+#             */
/*   Updated: 2024/12/25 00:23:11 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_game *cub, char *title)
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
										&cub->image.bits_per_pixel,
										&cub->image.line_length,
										&cub->image.endian);
	if (!cub->image.addr)
		allocation_error(cub, "Error: Unable to get image data address");
}

int main(void)
{
	t_game	cub;

	ft_bzero(&cub, sizeof(t_game));
	init_window(&cub, WIN_TITLE);
	print_data(&cub);
	return (EXIT_SUCCESS);
}