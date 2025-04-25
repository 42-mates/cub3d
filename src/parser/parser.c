/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:13:57 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/25 15:02:38 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int line_is_empty(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

int is_map_line(char *line)
{
    char    *trimmed;
    int     is_map_line;

    is_map_line = 0;
    trimmed = ft_strtrim(line, " ");
    if (trimmed[0] == '0' || trimmed[0] == '1')
        is_map_line = 1;
    free(trimmed);
    return (is_map_line);
}

void    map_list_append(t_game *cub, char *line, t_map_node **head)
{
    t_map_node  *current;
    t_map_node  *new_node;
    
    new_node = malloc(sizeof(t_map_node));
    if (!new_node)
        error_exit(cub, "malloc failed");
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

void    identify_line_type(char *line, t_game *cub)
{
    if (is_config_line(line))
        parse_config(line, cub);
    else if (is_map_line(line))
        map_list_append(cub, line, &cub->map.temp_list);
    else if (!line_is_empty(line))
    {
        printf("Error\nInvalid line in .cub file: %s\n", line);
        free(line);
        purge_gnl(cub->map.fd);
        close(cub->map.fd);
        exit_code(cub, 1);
    }
}

void    parse_scene_file(char *file_name, t_game *cub)
{
    char    *line;

    line = open_file(file_name, cub);
    while (line)
    {
        if (line_is_empty(line))
        {
            free(line);
            line = get_next_line(cub->map.fd);
            continue;
        }
        remove_newline(line);
        identify_line_type(line, cub);
        free(line);
        line = get_next_line(cub->map.fd);
    }
    close(cub->map.fd);
}
