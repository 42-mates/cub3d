/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:57:56 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/29 18:09:30 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char *check_syntax(char *trimmed, char *temp, int n)
{
	if (ft_strchr(trimmed, '+'))
		return ("'+' symbol in RGB values is rejected");
	if (ft_strcmp(trimmed, temp) || ft_strchr(trimmed, '-'))
		return ("RGB values must be positive integers (0-255)");
	if (n > 255)
		return ("RGB value out of range 0-255");
	return (NULL);
}

static int	parse_component(char *trimmed, t_game *cub, char **rgb, char *line)
{
	char	*temp;
	char	*msg;
	int		n;

	n = ft_atoi(trimmed);
	temp = ft_itoa(n);
	msg = check_syntax(trimmed, temp, n);
	if (msg != NULL)
	{
		free(line);
		free(temp);
		free(trimmed);
		free_tab(rgb);
		error_close_exit(cub, msg);
	}
	free(trimmed);
	free(temp);
	return (n);
}

static int	convert_rgb(char *line, t_game *cub, char *tmp)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free(tmp);
		free_tab(rgb);
		error_close_exit(cub, "RGB: need exactly three numbers");
	}
	r = parse_component(ft_strtrim(rgb[0], " "), cub, rgb, tmp);
	g = parse_component(ft_strtrim(rgb[1], " "), cub, rgb, tmp);
	b = parse_component(ft_strtrim(rgb[2], " "), cub, rgb, tmp);
	free_tab(rgb);
	return ((r << 16) | (g << 8) | b);
}

int	parse_rgb_line(t_game *cub, char *line, int *dst)
{
	char	*tmp;
	int		rgb;

	tmp = line;
	if (*dst != -1)
	{
		free(tmp);
		error_close_exit(cub, "Double config line");
	}
	++line;
	while (*line && (*line == ' ' || *line == '\t'))
		++line;
	rgb = convert_rgb(line, cub, tmp);
	return (rgb);
}
