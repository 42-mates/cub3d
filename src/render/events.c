/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:00:22 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/11 00:32:33 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_player(t_player *p, double angle)
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

// TODO : handle key release
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		exit_success(game);
	else if (keycode == XK_w)
		move_forward(game);
	else if (keycode == XK_s)
		move_backward(game);
	else if (keycode == XK_d)
		strafe_right(game);
	else if (keycode == XK_a)
		strafe_left(game);
	else if (keycode == XK_Left)
		rotate_player(&game->player, -ROT_SPEED);
	else if (keycode == XK_Right)
		rotate_player(&game->player, ROT_SPEED);
	else if (keycode == XK_m)
		game->minimap = !game->minimap;
	render_frame(game);
	return (0);
}
