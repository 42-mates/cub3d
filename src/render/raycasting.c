/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:39:55 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/24 17:52:33 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Executes the Digital Differential Analysis (DDA) algorithm.
 * 
 * Iteratively steps through the map grid until a wall ('1') is hit.
 * Chooses the smallest side distance (X or Y) at each step and updates the map position.
 * Also marks which side (vertical or horizontal) was hit.
 */
static void	perform_dda(t_game *cub, t_ray *ray)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->s_dist_x < ray->s_dist_y)
		{
			ray->s_dist_x += ray->d_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->s_dist_y += ray->d_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cub->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

/**
 * Initializes step direction and initial side distances for DDA.
 *
 * Based on the ray direction, determines the direction of step_x and step_y.
 * Also calculates the initial side distances from the player to the first side
 * of the next grid square in X and Y.
 */
static void	init_ray_step(t_game *cub, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->s_dist_x = (cub->player.pos_x - ray->map_x) * ray->d_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->s_dist_x = (ray->map_x + 1.0 - cub->player.pos_x) * ray->d_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->s_dist_y = (cub->player.pos_y - ray->map_y) * ray->d_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->s_dist_y = (ray->map_y + 1.0 - cub->player.pos_y) * ray->d_dist_y;
	}
}

/**
 * Initializes the direction and delta distances for the current ray.
 *
 * Calculates the ray direction based on player's direction and camera plane.
 * Determines the initial map cell the ray starts in, and computes delta distances
 * for stepping in the grid (distance to the next X or Y side).
 */
static void	init_ray_direction(t_game *cub, t_ray *ray, double camera_x)
{
	ray->dir_x = cub->player.dir_x + cub->player.plane_x * camera_x;
	ray->dir_y = cub->player.dir_y + cub->player.plane_y * camera_x;
	ray->map_x = (int)cub->player.pos_x;
	ray->map_y = (int)cub->player.pos_y;
	ray->d_dist_x = 1.0;
	ray->d_dist_y = 1.0;
	if (ray->dir_x != 0)
		ray->d_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y != 0)
		ray->d_dist_y = fabs(1 / ray->dir_y);
}

/**
 * Casts a single ray for the given screen column.
 *
 * Coordinates the full raycasting process:
 * - Initializes ray direction and stepping info
 * - Performs DDA to detect wall collision
 * - Computes perpendicular distance from the player to the wall hit
 */
static void	cast_ray(t_game *cub, t_ray *ray, double camera_x)
{
	double	pos_x;
	double	pos_y;
    
    pos_x = cub->player.pos_x;
    pos_y = cub->player.pos_y;
	init_ray_direction(cub, ray, camera_x);
	init_ray_step(cub, ray);
	perform_dda(cub, ray);
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - pos_x + (1 - ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->wall_dist = (ray->map_y - pos_y + (1 - ray->step_y) / 2.0) / ray->dir_y;
}

void	render_rays(t_game *cub)
{
	int		x;
	t_ray	ray;
	double	camera_x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
		ft_bzero(&ray, sizeof(t_ray));
		cast_ray(cub, &ray, camera_x);
		draw_wall_slice(cub, x, ray.wall_dist, ray.side);
		x++;
	}
}
