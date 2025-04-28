/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:00:22 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/28 14:38:22 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_press(int keycode, t_game *cub)
{
	if (keycode == XK_Escape)
		exit_success(cub);
	else if (keycode == XK_w || keycode == XK_W)
		cub->keys.w = 1;
	else if (keycode == XK_s || keycode == XK_S)
		cub->keys.s = 1;
	else if (keycode == XK_a || keycode == XK_A)
		cub->keys.a = 1;
	else if (keycode == XK_d || keycode == XK_D)
		cub->keys.d = 1;
	else if (keycode == XK_Left)
		cub->keys.left = 1;
	else if (keycode == XK_Right)
		cub->keys.right = 1;
	else if (keycode == XK_m || keycode == XK_M)
		cub->minimap = !cub->minimap;
	else if (keycode == XK_c || keycode == XK_C)
		cub->controls = !cub->controls;
	else if (keycode == XK_KP_Add && cub->map_scale < MAX_SCALE)
		cub->map_scale++;
	else if (keycode == XK_KP_Subtract && cub->map_scale > MIN_SCALE)
		cub->map_scale--;
	return (0);
}

static int	key_release(int keycode, t_game *cub)
{
	if (keycode == XK_w || keycode == XK_W)
		cub->keys.w = 0;
	else if (keycode == XK_s || keycode == XK_S)
		cub->keys.s = 0;
	else if (keycode == XK_a || keycode == XK_A)
		cub->keys.a = 0;
	else if (keycode == XK_d || keycode == XK_D)
		cub->keys.d = 0;
	else if (keycode == XK_Left)
		cub->keys.left = 0;
	else if (keycode == XK_Right)
		cub->keys.right = 0;
	return (0);
}

static int	game_loop(t_game *cub)
{
	if (cub->keys.w)
		move_forward(cub);
	if (cub->keys.s)
		move_backward(cub);
	if (cub->keys.a)
		strafe_left(cub);
	if (cub->keys.d)
		strafe_right(cub);
	if (cub->keys.left)
		rotate(&cub->player, -ROT_SPEED);
	if (cub->keys.right)
		rotate(&cub->player, ROT_SPEED);
	render_frame(cub);
	return (0);
}

void	init_hooks(t_game *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->win, 4, 1L << 2, mouse_press, cub);
	mlx_hook(cub->win, 5, 1L << 3, mouse_release, cub);
	mlx_hook(cub->win, 6, 1L << 6, mouse_move, cub);
	mlx_hook(cub->win, 17, 0L, exit_success, cub);
	mlx_loop_hook(cub->mlx, game_loop, cub);
}
