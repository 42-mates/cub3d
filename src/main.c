/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:42:38 by oprosvir          #+#    #+#             */
/*   Updated: 2024/12/23 22:12:44 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char *argv[])
{
    (void)argv;
	if (argc != 2)
	{
		ft_putendl_fd("\033[1;31mError: Invalid number of arguments\033[0m", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}