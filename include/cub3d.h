/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:47:07 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/05 17:26:05 by mglikenf         ###   ########.fr       */
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

typedef struct s_temp_map
{
	t_map_node		*top;
	unsigned int	height;
}					t_temp_map;

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
void			allocation_error(t_game *cub, const char *message);
void			exit_code(t_game *cub, int exit_code);
int				exit_success(t_game *cub);

// map & config parser
void    		extract_map(char *file_name, t_game *cub);
void    		extract_line(char *line, t_game *cub, t_temp_map *map_list);
void    		map_list_append(char *line, t_temp_map *map_list);
int 			map_list_size(t_map_node *head);

// render
void			render_frame(t_game *game);
void			put_pixel(t_image *img, int x, int y, int color);
void			draw_minimap(t_game *game, int map_scale);
int				handle_keypress(int keycode, t_game *cub);

// debug
void			print_data(const t_game *cub);

#endif