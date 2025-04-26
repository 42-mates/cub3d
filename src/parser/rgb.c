/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:57:56 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/27 01:19:44 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int skip_ws(const char *s, int i)
{
	while (s[i] == ' ' || s[i] == '\t')
		++i;
	return (i);
}

static int  parse_component(char *tok, t_game *cub)
{
	int i;
	long n;
	
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

// @mglikenf	bugs fixed
//				return color (not only separate rgb val) 
//				func name parse_rgb_line / parse_rgb
int  separate_rgb_values(t_game *cub, char *line)
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

// int rgb_to_int(int r, int g, int b)
// {
// 	int color;

// 	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
// 		return (-1);
// 	color = (r << 16) | (g << 8) | b;
// 	return (color);
// }

// // empty line after ident = segfault
// // skips simbols before/after number
// // negative num
// int separate_rgb_values(t_game *cub, char *line)
// {
// 	char	**rgb;
// 	char	*tmp;
// 	int		i;
// 	int		value;

// 	i = 0;
// 	while (!ft_isdigit(line[i]))
// 		i++;
// 	tmp = ft_substr(line, i, ft_strlen(line) - i);
// 	if (!tmp)
// 		error_exit(cub, "Malloc failed");
// 	rgb = ft_split(tmp, ',');
// 	free(tmp);
// // 	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
// //		error_exit(cub, "Malloc failed");
// 	if (!rgb)
// 		error_exit(cub, "Malloc failed");
// 	value = rgb_to_int(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2])); 
// 	free_tab(rgb);
// 	if (value == -1  || !rgb[0] || !rgb[1] || !rgb[2]) // invalid read
// 		error_exit(cub, "RGB values must be between 0 and 255");
// 	return (value);
// }
