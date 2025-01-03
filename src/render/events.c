/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:00:22 by oprosvir          #+#    #+#             */
/*   Updated: 2025/01/03 21:18:44 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO : handle key release
int	handle_keypress(int keycode, t_game *cub)
{
	if (keycode == XK_Escape)
		exit_success(cub);
	else if (keycode == XK_w)
		cub->player.pos_y -= 5;
	else if (keycode == XK_s)
		cub->player.pos_y += 5;
	else if (keycode == XK_a)
		cub->player.pos_x -= 5;
	else if (keycode == XK_d)
		cub->player.pos_x += 5;
	else if (keycode == XK_m)
		cub->minimap = !cub->minimap;
	render_frame(cub);
	return (0);
}
