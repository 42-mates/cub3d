/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:42:38 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/07 20:03:08 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO : process non-square maps
void init_map(t_game *game, char **map_grid)
{
	game->map.height = 0;
	while (map_grid[game->map.height])
		game->map.height++;
	game->map.width = ft_strlen(map_grid[0]);
	game->map.grid = map_grid;
}

void	check_args(int argc, char **argv)
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

int	main(int argc, char **argv)
{
	t_game cub;
	
	check_args(argc, argv);
	cub = init_game();
	print_data(&cub);
	extract_map(argv[1], &cub);
	init_map(&cub, cub.map.grid);
	// add : parser(argv[1], &cub);
	render_frame(&cub);
	mlx_hook(cub.win, 17, 0, exit_success, &cub);
	mlx_key_hook(cub.win, handle_keypress, &cub);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}
