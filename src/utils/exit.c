/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:56:37 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/23 01:40:54 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

// @mglikenf	malloc in ft_substr in extract_path func
//				-> need to free() textures
static void	free_map(t_map *m)
{
	free_tab(m->grid);
	free(m->no_texture);
	free(m->so_texture);
	free(m->we_texture);
	free(m->ea_texture);
	// if (m->temp_list)
	// {
	// 	deallocate_linked_list(m->temp_list);
	// 	m->temp_list = NULL;
	// }
}

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

// @mglikenf	safe clean-up, use instead of exit_failure
void	error_exit(t_game *cub, const char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	exit_code(cub, EXIT_FAILURE);
}

// @mglikenf 	no clean-up
// 				no free(grid)
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
