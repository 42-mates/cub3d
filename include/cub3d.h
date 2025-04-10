/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:47:07 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/11 00:19:29 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>

# define WIN_TITLE "cub3D"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05 // radians (~2.8 degrees per frame)

typedef struct s_map
{
	int			width;
	int			height;
	char		**grid;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_rgb;
	int			ceiling_rgb;
}				t_map;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			minimap;
	t_image		image;
	t_player	player;
	t_map		map;
}				t_game;

// main, init & exit
t_game			init_game(void);
void			allocation_error(t_game *cub, const char *message);
void			exit_code(t_game *cub, int exit_code);
int				exit_success(t_game *cub);

// render
void    		get_player_position(t_game *game);
void			render_frame(t_game *game);
void			put_pixel(t_image *img, int x, int y, int color);
void			draw_minimap(t_game *game, int map_scale);
int				handle_keypress(int keycode, t_game *cub);
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			strafe_right(t_game *game);
void			strafe_left(t_game *game);

// debug
void			print_data(const t_game *cub);

#endif