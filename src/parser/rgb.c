/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:57:56 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/28 10:27:48 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int skip_ws(const char *s, int i)
{
	if (!s)
		return (i);
	while (s[i] == ' ' || s[i] == '\t')
		++i;
	return (i);
}

static int  parse_component(char *tok, t_game *cub)
{
	int i;
	long n;
	
	if (!tok)
		error_exit(cub, "RGB: split failed");
	i = skip_ws(tok, 0);
	if (!ft_isdigit(tok[i]))
		error_exit(cub, "RGB values must be positive integers (0-255)");
	n = 0;
	while (ft_isdigit(tok[i]))
		n = n * 10 + (tok[i++] - '0');
	i = skip_ws(tok, i);
	if (tok[i] != '\0')
		error_exit(cub, "RGB: invalid character");
	if (n > 255)
		error_exit(cub, "RGB value out of range 0-255");
	return ((int)n);
}

int  parse_rgb_line(t_game *cub, char *line)
{
	char **rgb;
	int r;
	int g;
	int b;
	
	++line;
	while (*line && (*line == ' ' || *line == '\t'))
		++line;
	if (!ft_isdigit(*line))
		error_exit(cub, "RGB values must be positive integers (0-255)");
	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		error_exit(cub, "RGB: need exactly three numbers");
	r = parse_component(rgb[0], cub);
	g = parse_component(rgb[1], cub);
	b = parse_component(rgb[2], cub);
	free_tab(rgb);
	return ((r << 16) | (g << 8) | b);
}
