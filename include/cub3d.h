/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:47:07 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/10 00:28:17 by mglikenf         ###   ########.fr       */
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
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

typedef struct		s_map_node
{
	char				*line;
	struct s_map_node	*next;
	int					width;
} 					t_map_node;

// typedef struct s_temp_map
// {
// 	t_map_node		*top;
// 	unsigned int	height;
// }					t_temp_map;

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
	int			pos_x;
	int			pos_y;
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
void			check_args(int argc, char **argv);;
void			allocation_error(t_game *cub, const char *message);
void			exit_code(t_game *cub, int exit_code);
int				exit_success(t_game *cub);
void			exit_failure(char *msg);

// map & config parser
void    		parse_scene_file(char *file_name, t_game *cub);
// void    		extract_line(char *line, t_game *cub, t_temp_map *map_list);
void    		map_list_append(char *line, t_map_node **map_line);
int 			is_map_line(char *line);
int 			line_is_empty(char *line);
int 			is_config_line(char *trimmed);
void    		parse_config(char *line, t_game *cub);
char    		*extract_path(char *trimmed, int i);
void    		deallocate_linked_list(t_map_node *map_lines);
int 			convert_rgb_to_int(int red, int green, int blue);
int 			separate_rgb_values(char *line);
void			save_map_to_grid(t_map_node *lines, t_game *cub);

// render
void			render_frame(t_game *game);
void			put_pixel(t_image *img, int x, int y, int color);
void			draw_minimap(t_game *game, int map_scale);
int				handle_keypress(int keycode, t_game *cub);

// debug
void			print_data(const t_game *cub);
void    		print_temp_list(t_map_node *map_lines);

#endif