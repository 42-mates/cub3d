/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:41:30 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/28 14:39:16 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	extract_path(char *line, int i, char **dst, t_game *cub)
{
	char	*trimmed;

	if (*dst)
	{
		free(line);
		purge_gnl(cub->map.fd);
		close(cub->map.fd);
		error_exit(cub, "Double config line");
	}
	while (line[i] == ' ')
		i++;
	trimmed = ft_substr(line, i, ft_strlen(line) - i);
	if (!trimmed)
	{
		free(line);
		purge_gnl(cub->map.fd);
		close(cub->map.fd);
		error_exit(cub, "Malloc fail");
	}
	*dst = trimmed;
}

void	parse_config(char *line, t_game *cub, int *map_started)
{
	if ((*map_started))
	{
		free(line);
		purge_gnl(cub->map.fd);
		close(cub->map.fd);
		error_exit(cub, "Map content must be last");
	}
	while (*line && (*line == ' ' || *line == '\t'))
		++line;
	if (ft_strncmp(line, "NO", 2) == 0)
		extract_path(line, 2, &cub->map.no_texture, cub);
	else if (ft_strncmp(line, "SO", 2) == 0)
		extract_path(line, 2, &cub->map.so_texture, cub);
	else if (ft_strncmp(line, "WE", 2) == 0)
		extract_path(line, 2, &cub->map.we_texture, cub);
	else if (ft_strncmp(line, "EA", 2) == 0)
		extract_path(line, 2, &cub->map.ea_texture, cub);
	else if (ft_strncmp(line, "F", 1) == 0)
		cub->map.floor_rgb = parse_rgb_line(cub, line);
	else if (ft_strncmp(line, "C", 1) == 0)
		cub->map.ceiling_rgb = parse_rgb_line(cub, line);
}

int	is_config_line(char *s)
{
	while (*s == ' ' || *s == '\t')
		++s;
	return (!ft_strncmp(s, "NO ", 3) || !ft_strncmp(s, "SO ", 3)
		|| !ft_strncmp(s, "WE ", 3) || !ft_strncmp(s, "EA ", 3)
		|| !ft_strncmp(s, "F ", 2) || !ft_strncmp(s, "C ", 2));
}
