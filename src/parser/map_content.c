/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:06:32 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/10 22:45:52 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int append_players(char *line)
{
    char    *orientation_set = "NEWSnews";
    int     i;
    int     count;

    i = 0;
    count = 0;
    while (line[i])
    {
        if (ft_strchr(orientation_set, line[i]))
            count++;
        i++;
    }
    return (count);
}

int     line_has_invalid_chars(char *line)
{
    char    *valid_set;
    int     i;

    valid_set = "10 NEWSnews";
    i = 0;
    while (line[i])
    {
        if (!ft_strchr(valid_set, line[i]))
        {
            printf("line contains an invalid character = %c\n", line[i]);
            return (1);
        }
        i++;
    }
    return (0);
}

int validate_map_lines(t_map_node *head)
{
    t_map_node  *current;
    int         num_of_players;

    current = head;
    num_of_players = 0;
    while (current)
    {
        if (line_has_invalid_chars(current->line))
            return (1);
        num_of_players += append_players(current->line);
        current = current->next;
    }
    if (num_of_players != 1)
    {
        printf("no players at all or too many");
        return (1);
    }
    return (0);
}

void	validate_map_content(t_game *cub)
{
	if (validate_map_lines(cub->map.temp_list))
    {
        printf("map is invalid\n");
        // cleanup and exit
    }
    
    save_map_to_grid(cub->map.temp_list, cub);
}
