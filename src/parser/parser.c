/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mglikenf <mglikenf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:13:57 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/25 00:57:04 by mglikenf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// @mglikenf    long func name (free_map_list, free_tmp_list, free_list)
//              memory leaks free(tmp->line); malloc in ft_strdup() in map_list_append
void    deallocate_linked_list(t_map_node *head)
{
    t_map_node  *current;
    t_map_node  *tmp;

    current = head;
    while (current)
    {
        tmp = current;
        current = current->next;
        free(tmp->line);
        free(tmp);
    }
}

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

void    map_list_append(char *line, t_map_node **head)
{
    t_map_node  *current;
    t_map_node  *new_node;
    
    new_node = malloc(sizeof(t_map_node));
    if (!new_node)
    {
        printf("malloc failed\n");
        exit(1);
    }
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

    cub->fd = open(file_name, O_RDONLY);
    if (cub->fd < 0)
    {
        printf("Error\nFile cannot be opened\n");
        exit_code(cub, 1);
    }
    line = get_next_line(cub->fd);
    if (!line)
    {
        close(cub->fd);
        printf("Error\nEmpty file\n");
        exit_code(cub, 1);
    }
    return (line);
}

void    identify_line_type(char *line, t_game *cub)
{
    if (is_config_line(line))
        parse_config(line, cub);
    else if (is_map_line(line))
        map_list_append(line, &cub->map.temp_list);
    else if (!line_is_empty(line))
    {
        printf("Error\nInvalid line in .cub file: %s\n", line);
        free(line);
        close(cub->fd);
        free_memory_and_exit(cub);
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
            line = get_next_line(cub->fd);
            continue;
        }
        remove_newline(line);
        identify_line_type(line, cub);
        free(line);
        line = get_next_line(cub->fd);
    }
    close(cub->fd);
}


/***********************************/

// void    parse_scene_file(char *file_name, t_game *cub)
// {
//     char        *line;
//     int         map_started;
    
//     map_started = 0;
//     cub->fd = open(file_name, O_RDONLY);
//     if (cub->fd < 0)
//     {
//         printf("Error\nFile cannot be opened\n");
//         exit_code(cub, 1);
//     }
//     line = get_next_line(cub->fd);
//     if (line == NULL)
//     {
//         close(cub->fd);
//         printf("Error\nEmpty file\n");
//         exit_code(cub, 1);
//     }
//     while ((line = get_next_line(cub->fd)))
//     {
//         remove_newline(line);
//         if (line_is_empty(line))
//         {
//             free(line);
//             continue;
//         }
//         if (!map_started && is_config_line(line))
//             parse_config(line, cub);
//         else if (is_map_line(line))
//         {
//             map_started = 1;
//             map_list_append(line, &cub->map.temp_list);
//         }
//         else if (map_started && is_config_line(line))
//         {
//             free(line);
//             close(cub->fd);
//             printf("Error\nInvalid file: map content must be last\n");
//             free_memory_and_exit(cub);
//             exit_code(cub, 1);
//         }
//         else
//         {
//             free(line);
//             close(cub->fd);
//             printf("Error\nInvalid line in .cub file\n");
//             free_memory_and_exit(cub);
//             exit_code(cub, 1);
//         }
//         free(line);
//     }
//     free(line);
//     close(cub->fd);
// }
