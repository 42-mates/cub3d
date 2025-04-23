/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:13:57 by mglikenf          #+#    #+#             */
/*   Updated: 2025/04/23 01:25:10 by oprosvir         ###   ########.fr       */
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
    // multiple newline characters ?
}

void    parse_scene_file(char *file_name, t_game *cub)
{
    int         fd;
    char        *line;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        exit_failure("File can't be opened");
    line = get_next_line(fd);
    if (line == NULL)
    {
        close(fd);
        exit_failure("Empty file");
    }
    while (line != NULL)
    {
        remove_newline(line);
        if (is_config_line(line))
            parse_config(line, cub);
        else if (is_map_line(line))
            map_list_append(line, &cub->map.temp_list);
        else if (!line_is_empty(line))
        {
            // // handle memory leaks
            // close(fd);
            // free(line);
            break ;
        }
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    free(line);
}
