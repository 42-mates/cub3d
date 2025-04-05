/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:42:38 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/05 17:06:13 by mglikenf         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_game cub;
	
	// char *map_grid[] =
	// {
	// 	"11111111",
	// 	"10000001",
	// 	"11100101",
	// 	"10000001",
	// 	"10000111",
	// 	"10100001",
	// 	"10100001",
	// 	"11111111",
	// 	NULL
	// };

	// add : check_args(argc, argv);
	if (argc != 2)
	{
		printf("Error: Invalid number of arguments\n");
		exit(1);
	}
	cub = init_game();
	print_data(&cub);
	extract_map(argv[1], &cub);
	// init_map(&cub, map_grid);
	init_map(&cub, cub.map.grid);
	// add : parser(argv[1], &cub);
	render_frame(&cub);
	mlx_hook(cub.win, 17, 0, exit_success, &cub);
	mlx_key_hook(cub.win, handle_keypress, &cub);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}
