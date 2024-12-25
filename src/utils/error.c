/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:31:22 by oprosvir          #+#    #+#             */
/*   Updated: 2024/12/25 00:40:28 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	allocation_error(t_game *cub, const char *message)
{
	ft_putendl_fd(message, 2);
	exit_code(cub, EXIT_FAILURE);
}