/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:00:22 by oprosvir          #+#    #+#             */
/*   Updated: 2024/12/25 19:12:01 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keycode, t_game *cub)
{
	if (keycode == XK_Escape)
		exit_success(cub);
	return (0);
}