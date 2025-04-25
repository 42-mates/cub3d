/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:14:35 by oprosvir          #+#    #+#             */
/*   Updated: 2025/04/25 14:19:36 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void    free_tmp_list(t_map_node *head)
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

void	free_map(t_map *m)
{
	free_tab(m->grid);
	free(m->no_texture);
	free(m->so_texture);
	free(m->we_texture);
	free(m->ea_texture);
	if (m->temp_list)
	{
		free_tmp_list(m->temp_list);
		m->temp_list = NULL;
	}
}

