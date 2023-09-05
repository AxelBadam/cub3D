/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:06:36 by ekoljone          #+#    #+#             */
/*   Updated: 2023/09/05 15:51:24 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_for_invalid_attributes(t_cubed *cubed, char **map)
{
	if (!cubed->map.path_to_east || !cubed->map.path_to_west
		|| !cubed->map.path_to_north || !cubed->map.path_to_south)
		error_exit(cubed, "PATH ERROR\n");
	if (!cubed->map.C_color_check || !cubed->map.F_color_check)
		error_exit(cubed, "COLOR ERROR\n");
	check_map(cubed, map);
}

void	check_map(t_cubed *cubed, char **map)
{
	int	row;
	int	spawn;

	spawn = 0;
	row = 0;
	while (map[row])
	{
		if (row == 0 || map[row + 1] == NULL)
			check_top_and_bottom(cubed, map[row]);
		check_row(cubed, map[row], &spawn);
		if (map[row + 1])
		{
			if (!check_if_walls_connect(map[row], map[row + 1]))
				error_exit(cubed, "INVALID MAP\n");
		}
		row++;
	}
	if (spawn == 0 || spawn > 1)
		error_exit(cubed, "INVALID SPAWN\n");
}

void	check_row(t_cubed *cubed, char *row, int *spawn)
{
	int	index;

	index = 0;
	while (row[index])
	{
		check_index_spot(cubed, row[index]);
		*spawn += check_direction(row[index++]);
	}
}

int	check_if_walls_connect(char *row, char *next_row)
{
	int	ctr;
	int	first_wall;
	int	second_wall;

	ctr = 0;
	first_wall = 0;
	second_wall = 0;
	ctr = check_wall(row, next_row, &first_wall);
	while ((row[ctr] && (row[ctr] == '0' || row[ctr] == '1'
				|| ft_is_white_space(row[ctr]) || check_direction(row[ctr]))))
	{
		if (row[ctr] == '1' && !ft_strchr(&row[ctr], '0') && !ft_strchr(&row[ctr], ' ')
			&& !ft_strchr(&next_row[ctr], '0') && !ft_strchr(&next_row[ctr], ' '))
		{
			check_wall(&row[ctr], &next_row[ctr], &second_wall);
			break ;
		}
		ctr++;
	}
	if (second_wall && first_wall)
		return (1);
	return (0);
}

int	check_wall(char *row, char *next_row, int *wall)
{
	int	ctr;

	ctr = 0;
	while (row[ctr] && (row[ctr] == '1'
			|| ft_is_white_space(row[ctr]) || check_direction(row[ctr])))
	{
		if (next_row[ctr] && row[ctr] == '1' && next_row[ctr] == '1')
		{
			*wall = 1;
			break ;
		}
		ctr++;
	}
	return (ctr);
}
