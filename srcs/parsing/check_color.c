/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:08:59 by mdahani           #+#    #+#             */
/*   Updated: 2025/08/20 14:43:07 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool check_color(t_map *map)
{
    char **f_color, **c_color;
    int number_of_commas = 0, f_count = 0, c_count = 0;

    // check number of commas in every color
    int i = 0;
    while (map->f_color[i])
    {
        if (map->f_color[i] == ',')
            number_of_commas++;
        i++;
    }
    if (number_of_commas != 2)
        return (false);
    i = 0;
    number_of_commas = 0;
    while (map->c_color[i])
    {
        if (map->c_color[i] == ',')
            number_of_commas++;
        i++;
    }
    if (number_of_commas != 2)
        return (false);

    // check number of colors
    f_color =  ft_split(map->f_color, ',');
    c_color =  ft_split(map->c_color, ',');

    i = 0;
    while (f_color[i])
    {
        if (ft_atoi(f_color[i]) < 0 || ft_atoi(f_color[i]) > 255)
            return (false);
        int j = 0;
        while (f_color[i][j])
        {        
            if (!ft_isdigit(f_color[i][j]))
                return (false);
            j++;
        }
        i++;
        f_count++;
    }
    i = 0;
    while (c_color[i])
    {
      
        if (ft_atoi(c_color[i]) < 0 || ft_atoi(c_color[i]) > 255)
            return (false);
        int j = 0;
        while (c_color[i][j])
        {
            if (!ft_isdigit(c_color[i][j]))
                return (false);
            j++;
        }   
        i++;
        c_count++;
    }
    if (f_count != 3 || c_count != 3)
        return (false);
    return (true);
}
