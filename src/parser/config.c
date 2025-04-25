/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:41:30 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/25 14:28:28 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char    *extract_path(char *trimmed, int i)
{
    while (trimmed[i] == ' ')
        i++;
    return (ft_substr(trimmed, i, ft_strlen(trimmed) - i));
}

void    parse_config(char *line, t_game *cub)
{
    char    *trimmed;

    trimmed = ft_strtrim(line, " ");
    if (ft_strncmp(trimmed, "NO", 2) == 0)
        cub->map.no_texture = extract_path(trimmed, 2);
    else if (ft_strncmp(trimmed, "SO", 2) == 0)
        cub->map.so_texture = extract_path(trimmed, 2);
    else if (ft_strncmp(trimmed, "WE", 2) == 0)
        cub->map.we_texture = extract_path(trimmed, 2);
    else if (ft_strncmp(trimmed, "EA", 2) == 0)
        cub->map.ea_texture = extract_path(trimmed, 2);
    else if (ft_strncmp(trimmed, "F", 1) == 0)
        cub->map.floor_rgb = separate_rgb_values(cub, trimmed);
    else if (ft_strncmp(trimmed, "C", 1) == 0)
        cub->map.ceiling_rgb = separate_rgb_values(cub, trimmed);
    free(trimmed);
}

int is_config_line(char *trimmed)
{
    return (!ft_strncmp(trimmed, "NO ", 3) || 
            !ft_strncmp(trimmed, "SO ", 3) || 
            !ft_strncmp(trimmed, "WE ", 3) || 
            !ft_strncmp(trimmed, "EA ", 3) || 
            !ft_strncmp(trimmed, "F ", 2) || 
            !ft_strncmp(trimmed, "C ", 2));
}
