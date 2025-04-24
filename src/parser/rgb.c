/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:57:56 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/24 18:14:49 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    free_split(char **split)
{
    int i;

    i = 0;
    if (!split)
        return;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

int convert_rgb_to_int(int red, int green, int blue)
{
	int color;

	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255) 
		return (-1);
	color = (red << 16) | (green << 8) | blue;
	return (color);
}

// @mglikenf	exit -> need to free memory, add cub to param
//				try to malloc -> check if it's failed (ft_substr, ft_split)
//				memory leaks, you need to free tab
int separate_rgb_values(char *line)
{
	char	**rgb;
	char	*tmp;
	int		i;
	int		value;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	tmp = ft_substr(line, i, ft_strlen(line) - i);
	// if (!tmp)
	// 	error_exit(cub, "Malloc failed");
	rgb = ft_split(tmp, ',');
	free(tmp);
	// if (!rgb)
	// 	error_exit(cub, "Malloc failed");
	value = convert_rgb_to_int(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	free_tab(rgb);
	if (value == -1)
		error_exit(NULL, "RGB values must be between 0 and 255");
	return (value);
}
