/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:47:07 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/13 19:59:52 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

# define WIN_TITLE "cub3D"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define MOVE_SPEED 0.01
# define ROT_SPEED 0.01 // radians
# define BLACK 0x000000
# define WHITE 0xFFFFFF

typedef struct		s_map_node
{
	char				*line;
	struct s_map_node	*next;
} 					t_map_node;

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
	t_map_node	*temp_list;
}				t_map;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keys;

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
	t_keys		keys;
	t_map		map;
}				t_game;

// main, init & exit
void			allocation_error(t_game *cub, const char *message);
void			exit_code(t_game *cub, int exit_code);
int				exit_success(t_game *cub);
void			exit_failure(char *msg);

// map & config parser
void    		parse_scene_file(char *file_name, t_game *cub);
void    		remove_newline(char *line);
void    		map_list_append(char *line, t_map_node **head);
int 			is_map_line(char *line);
int 			line_is_empty(char *line);
void			validate_map_content(t_game *cub);
int 			validate_map_lines(t_map_node *head);
int     		line_has_invalid_chars(char *line);
int 			append_players(char *line);
int 			is_config_line(char *trimmed);
void    		parse_config(char *line, t_game *cub);
char    		*extract_path(char *trimmed, int i);
void    		deallocate_linked_list(t_map_node *map_lines);
int 			convert_rgb_to_int(int red, int green, int blue);
int 			separate_rgb_values(char *line);
void			save_map_to_grid(t_map_node *lines, t_game *cub);

// render
void			set_player_direction(t_game *game, char c);
void			render_frame(t_game *game);
void			put_pixel(t_image *img, int x, int y, int color);
void			draw_minimap(t_game *game, int map_scale);
int				handle_keypress(int keycode, t_game *cub);
int				handle_keyrelease(int keycode, t_game *game);
int				game_loop(t_game *game);
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			strafe_right(t_game *game);
void			strafe_left(t_game *game);

// debug
void			print_data(const t_game *cub);
void    		print_temp_list(t_map_node *map_lines);

#endif