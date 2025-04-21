/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:43:24 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/21 22:27:16 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

int	mouse_press(int button, int x, int y, t_game *cub)
{
	(void)y;
	if (button == 1) // left mouse button
	{
		cub->keys.m_down = 1;
		cub->keys.x_old = x;
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *cub)
{
	(void)x;
	(void)y;
	if (button == 1)
        cub->keys.m_down = 0;
	return (0);
}

int	mouse_move(int x, int y, t_game *cub)
{
	(void)y;
    int delta_x;

	if (!cub->keys.m_down)
		return (0);
	delta_x = x - cub->keys.x_old;
	if (delta_x != 0)
		rotate(&cub->player, delta_x * MOUSE_SENS);
    cub->keys.x_old = x;
	return (0);
}
