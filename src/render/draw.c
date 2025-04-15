/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:38:08 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/14 23:40:53 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO : draw textures
void	draw_wall_slice(t_game *cub, int x, double dist, int side)
{
	int	line_height;
	int	start;
	int	end;
	int	y;
	int	color;

	if (dist <= 0.01)
		dist = 0.01;
	line_height = WIN_HEIGHT / dist;
	start = -line_height / 2 + WIN_HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = line_height / 2 + WIN_HEIGHT / 2;
	if (end >= WIN_HEIGHT)
		end = WIN_HEIGHT - 1;
	if (side == 0)
		color = 0xAAAAAA;
	else
		color = 0x777777;
	y = start;
	while (y <= end)
	{
		put_pixel(&cub->image, x, y, color);
		y++;
	}
}
