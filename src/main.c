/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:42:38 by oprosvir          #+#    #+#             */
/*   Updated: 2025/05/01 19:16:45 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_args(int argc, char **argv)
{
	char	*s;
	int		fd;
	char	*filename;

	if (argc != 2)
		exit_failure("Invalid number of arguments");
	filename = ft_strrchr(argv[1], '/');
	if (filename)
		filename++;
	else
		filename = argv[1];
	if (filename[0] == '.')
		exit_failure("Hidden .cub files are not allowed");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
	{
		if (fd >= 0)
			close(fd);
		exit_failure("File does not exist or is a directory");
	}
	close(fd);
	s = ft_strrchr(argv[1], '.');
	if (!s || ft_strcmp(s, ".cub") || ft_strlen(s) != 4)
		exit_failure("Invalid file format");
}

static void	init_window(t_game *cub, char *title)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		error_exit(cub, "Unable to initialize MLX");
	load_textures(cub);
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, title);
	if (!cub->win)
		error_exit(cub, "Unable to create window");
	cub->image.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->image.img)
		error_exit(cub, "Unable to create image");
	cub->image.addr = mlx_get_data_addr(cub->image.img, &cub->image.bpp,
			&cub->image.line_len, &cub->image.endian);
	if (!cub->image.addr)
		error_exit(cub, "Unable to get image data address");
}

static void	get_player_position(t_game *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (j < cub->map.width)
		{
			if (ft_strchr("NSWE", cub->map.grid[i][j]))
			{
				cub->player.pos_x = j + 0.5;
				cub->player.pos_y = i + 0.5;
				set_player_direction(cub, cub->map.grid[i][j]);
				cub->map.grid[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

static void	init_game(t_game *cub)
{
	ft_bzero(cub, sizeof(t_game));
	cub->map_scale = MINIMAP_SCALE;
	cub->controls = 1;
	cub->map.floor_rgb = -1;
	cub->map.ceiling_rgb = -1;
}

int	main(int argc, char **argv)
{
	t_game	cub;

	check_args(argc, argv);
	init_game(&cub);
	parse_scene_file(argv[1], &cub);
	print_data(&cub);
	init_window(&cub, WIN_TITLE);
	get_player_position(&cub);
	render_frame(&cub);
	init_hooks(&cub);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}
