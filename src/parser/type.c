/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:06:32 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/30 15:26:13 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	is_map_line(char *line)
{
	char	*trimmed;
	char	*set;
	int		is_map_line;

	set = "10NSWE";
	is_map_line = 0;
	trimmed = ft_strtrim(line, " ");
	if (ft_strchr(set, trimmed[0]))
		is_map_line = 1;
	free(trimmed);
	return (is_map_line);
}

void	identify_line_type(char *line, t_game *cub, int *map_started,
		int *map_ended)
{
	if (!(*map_started) && line_is_empty(line))
		return ;
	if ((*map_ended) && line_is_empty(line))
	{
		free(line);
		error_close_exit(cub, "Detected symbols after map");
	}
	if (is_config_line(line))
		parse_config(line, cub, map_started);
	else if (is_map_line(line) || line_is_empty(line))
	{
		*map_started = 1;
		map_list_append(cub, line, &cub->map.temp_list);
	}
	else if (!line_is_empty(line))
	{
		free(line);
		error_close_exit(cub, "Invalid line in .cub file");
	}
}
