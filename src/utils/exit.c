/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:56:37 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/25 14:38:10 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_code(t_game *cub, int code)
{
	if (!cub)
		exit(code);
	free_map(&cub->map);
	if (cub->image.img)
		mlx_destroy_image(cub->mlx, cub->image.img);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	exit(code);
}

void	error_exit(t_game *cub, const char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	exit_code(cub, EXIT_FAILURE);
}

void	exit_failure(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	exit(1);
}

int	exit_success(t_game *cub)
{
	exit_code(cub, EXIT_SUCCESS);
	return (0);
}

void	purge_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}
