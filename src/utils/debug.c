/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:50:55 by oprosvir          #+#    #+#             */
/*   Updated: 2024/12/25 00:39:48 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_image_data(const t_image *image)
{
	printf("Image Data:\n");
	printf("  img: %p\n", image->img);
	printf("  addr: %p\n", image->addr);
	printf("  bits_per_pixel: %d\n", image->bits_per_pixel);
	printf("  line_length: %d\n", image->line_length);
	printf("  endian: %d\n", image->endian);
	printf("\n");
}

void print_data(const t_game *cub)
{
	int i;
	i = 0;
	printf("Game Data:\n");
	printf("  mlx: %p\n", cub->mlx);
	printf("  win: %p\n", cub->win);
	printf("  map:\n");
	if (cub->map)
	{
		while (cub->map[i])
		{
			printf("    %s\n", cub->map[i]);
			i++;
		}
	}
	else
		printf("    (null)\n");    
	print_image_data(&cub->image);
}
