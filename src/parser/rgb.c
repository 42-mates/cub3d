/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:57:56 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/28 00:18:27 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int convert_rgb_to_int(int red, int green, int blue)
{
	int color;

	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255) 
		return (-1);
	color = (red << 16) | (green << 8) | blue;
	return (color);
}

// check for substrings validated
int separate_rgb_values(t_game *cub, char *line)
{
	char	**rgb;
	char	*tmp;
	int		i;
	int		value;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	tmp = ft_substr(line, i, ft_strlen(line) - i);
	if (!tmp)
		error_exit(cub, "Malloc failed");
	rgb = ft_split(tmp, ',');
	free(tmp);
	if (!rgb)
		error_exit(cub, "Malloc failed");
	value = convert_rgb_to_int(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	if (value == -1  || !rgb[0] || !rgb[1] || !rgb[2])
	{
		free_tab(rgb);
		error_exit(cub, "RGB values must be between 0 and 255");
	}
	free_tab(rgb);
	return (value);
}
