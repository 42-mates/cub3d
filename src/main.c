/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:42:38 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/13 20:32:26 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_args(int argc, char **argv)
{
	char	*s;
	int		fd;

	if (argc != 2)
		exit_failure("Invalid number of arguments");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
	{
		close(fd);
		exit_failure("File does not exist or is a directory");
	}
	close(fd);
	s = ft_strchr(argv[1], '.');
	if (s)
	{
		if (ft_strcmp(s, ".cub") == 0 && ft_strlen(s) == 4)
			return ;
	}
	exit_failure("Invalid file format");
}

static void	init_window(t_game *cub, char *title)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		allocation_error(cub, "Error: Unable to initialize MLX");
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, title);
	if (!cub->win)
		allocation_error(cub, "Error: Unable to create window");
	cub->image.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->image.img)
		allocation_error(cub, "Error: Unable to create image");
	cub->image.addr = mlx_get_data_addr(cub->image.img,
			&cub->image.bits_per_pixel, &cub->image.line_length,
			&cub->image.endian);
	if (!cub->image.addr)
		allocation_error(cub, "Error: Unable to get image data address");
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

int	main(int argc, char **argv)
{
	t_game cub;
	
	check_args(argc, argv);
	ft_bzero(&cub, sizeof(t_game));
	init_window(&cub, WIN_TITLE);
	parse_scene_file(argv[1], &cub);
	validate_map_content(&cub);
	get_player_position(&cub);
	print_data(&cub);
	render_frame(&cub);
	mlx_hook(cub.win, 2, 1L << 0, handle_keypress, &cub);
	mlx_hook(cub.win, 3, 1L << 1, handle_keyrelease, &cub);
	mlx_hook(cub.win, 17, 0, exit_success, &cub);
	mlx_loop_hook(cub.mlx, game_loop, &cub);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}
