/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:57:20 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/22 22:31:18 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	try_move(t_game *cub, double new_x, double new_y)
{
	if (cub->map.grid[(int)cub->player.pos_y][(int)new_x] != '1')
		cub->player.pos_x = new_x;
	if (cub->map.grid[(int)new_y][(int)cub->player.pos_x] != '1')
		cub->player.pos_y = new_y;
}

void	move_forward(t_game *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos_x + cub->player.dir_x * MOVE_SPEED;
	new_y = cub->player.pos_y + cub->player.dir_y * MOVE_SPEED;
	try_move(cub, new_x, new_y);
}

void	move_backward(t_game *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos_x - cub->player.dir_x * MOVE_SPEED;
	new_y = cub->player.pos_y - cub->player.dir_y * MOVE_SPEED;
	try_move(cub, new_x, new_y);
}

void	strafe_right(t_game *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos_x + cub->player.plane_x * MOVE_SPEED;
	new_y = cub->player.pos_y + cub->player.plane_y * MOVE_SPEED;
	try_move(cub, new_x, new_y);
}

void	strafe_left(t_game *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos_x - cub->player.plane_x * MOVE_SPEED;
	new_y = cub->player.pos_y - cub->player.plane_y * MOVE_SPEED;
	try_move(cub, new_x, new_y);
}
