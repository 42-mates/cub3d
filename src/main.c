/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:42:38 by oprosvir          #+#    #+#             */
/*   Updated: 2024/12/29 20:58:10 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_game cub;

	// add : check_args(argc, argv);
	cub = init_game();
	print_data(&cub);

	// add : parser(argv[1], &cub);
	render_frame(&cub);
	mlx_hook(cub.win, 17, 0, exit_success, &cub);
	mlx_key_hook(cub.win, handle_keypress, &cub);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}
