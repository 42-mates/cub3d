/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:13:57 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/28 00:20:08 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    map_list_append(t_game *cub, char *line, t_map_node **head)
{
    t_map_node  *current;
    t_map_node  *new_node;
    
    new_node = malloc(sizeof(t_map_node));
    if (!new_node)
        error_exit(cub, "Malloc failed");
    new_node->line = ft_strdup(line);
    new_node->next = NULL;
    if (*head == NULL)
    {
        *head = new_node;
        return ;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new_node;
}

void    remove_newline(char *line)
{
    size_t  len;

    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
}

char    *open_file(char *file_name, t_game *cub)
{
    char    *line;

    cub->map.fd = open(file_name, O_RDONLY);
    if (cub->map.fd < 0)
        error_exit(cub, "File cannot be opened");
    line = get_next_line(cub->map.fd);
    if (!line)
    {
        close(cub->map.fd);
        error_exit(cub, "Empty file");
    }
    return (line);
}

void    parse_scene_file(char *file_name, t_game *cub)
{
    char    *line;
    int     map_started;
    // int     map_ended;

    line = open_file(file_name, cub);
    map_started = 0;
    // map_ended = 0;
    while (line)
    {
        // if (line_is_empty(line) && map_started)
        //     map_ended = 1;
        remove_newline(line);
        identify_line_type(line, cub, &map_started);
        free(line);
        line = get_next_line(cub->map.fd);
    }
    validate_map_lines(cub, cub->map.temp_list);
    save_map_to_grid(cub);
    validate_tiles(cub);
    close(cub->map.fd);
}
