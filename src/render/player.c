/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:09:02 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/15 21:05:24 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_north(t_game *cub)
{
	cub->player.dir_x = 0.0;
	cub->player.dir_y = -1.0;
	cub->player.plane_x = 0.66;
	cub->player.plane_y = 0.0;
}

static void	set_south(t_game *cub)
{
	cub->player.dir_x = 0.0;
	cub->player.dir_y = 1.0;
	cub->player.plane_x = -0.66;
	cub->player.plane_y = 0.0;
}

static void	set_east(t_game *cub)
{
	cub->player.dir_x = 1.0;
	cub->player.dir_y = 0.0;
	cub->player.plane_x = 0.0;
	cub->player.plane_y = 0.66;
}

static void	set_west(t_game *cub)
{
	cub->player.dir_x = -1.0;
	cub->player.dir_y = 0.0;
	cub->player.plane_x = 0.0;
	cub->player.plane_y = -0.66;
}

void	set_player_direction(t_game *cub, char c)
{
	if (c == 'N')
		set_north(cub);
	else if (c == 'S')
		set_south(cub);
	else if (c == 'E')
		set_east(cub);
	else if (c == 'W')
		set_west(cub);
}
