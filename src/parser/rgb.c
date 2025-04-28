/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:57:56 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/28 14:18:54 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	skip_ws(const char *s, int i)
{
	if (!s)
		return (i);
	while (s[i] == ' ' || s[i] == '\t')
		++i;
	return (i);
}

static int	parse_component(char *tok, t_game *cub, char **rgb, char *tmp)
{
	int		i;
	long	n;

	if (!tok)
		error_exit(cub, "RGB: split failed");
	i = skip_ws(tok, 0);
	if (!ft_isdigit(tok[i]))
	{
		free(tmp);
		free_tab(rgb);
		purge_gnl(cub->map.fd);
		error_exit(cub, "RGB values must be positive integers (0-255)");
	}
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

char	**tokenize_rgb(char *line, t_game *cub, char *tmp)
{
	char	**rgb;

	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free(tmp);
		free_tab(rgb);
		purge_gnl(cub->map.fd);
		error_exit(cub, "RGB: need exactly three numbers");
	}
	return (rgb);
}

int	parse_rgb_line(t_game *cub, char *line)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	char	*tmp;

	tmp = line;
	++line;
	while (*line && (*line == ' ' || *line == '\t'))
		++line;
	if (!ft_isdigit(*line))
	{
		free(tmp);
		purge_gnl(cub->map.fd);
		error_exit(cub, "RGB values must be positive integers (0-255)");
	}
	rgb = tokenize_rgb(line, cub, tmp);
	r = parse_component(rgb[0], cub, rgb, tmp);
	g = parse_component(rgb[1], cub, rgb, tmp);
	b = parse_component(rgb[2], cub, rgb, tmp);
	free_tab(rgb);
	return ((r << 16) | (g << 8) | b);
}
