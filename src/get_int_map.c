/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_int_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:13:37 by ekoljone          #+#    #+#             */
/*   Updated: 2023/09/05 15:01:41 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_int_map_size(t_cubed *cubed, char **map)
{
	int	size;
	int	row;

	size = 0;
	row = 0;
	while (map[row])
	{
		if (size < ft_strlen(map[row]))
			size = ft_strlen(map[row]);
		row++;
	}
	cubed->map.map_s = size * row;
	cubed->map.map_y = row;
	cubed->map.map_x = size;
}

void	fill_int(t_cubed *cubed, int *map_index, char map_char)
{
	if (ft_is_white_space(map_char))
		*map_index = 2;
	else if (map_char == 'W' || map_char == 'S'
		|| map_char == 'E' || map_char == 'N')
	{
		get_player_angle(cubed, map_char);
		*map_index = 3;
	}
	else
		*map_index = map_char - 48;
}

void	fill_int_array(t_cubed *cubed, char *row)
{
	static int	index;
	int			column;
	int			tmp;

	tmp = 0;
	column = 0;
	while (row[column])
	{
		fill_int(cubed, &cubed->map.map[index], row[column]);
		index++;
		column++;
		if (!row[column] && cubed->map.map_x > column)
		{
			tmp = column;
			while (tmp < cubed->map.map_x)
			{
				cubed->map.map[index++] = 2;
				tmp++;
			}
		}
	}
}

void	convert_map_to_int(t_cubed *cubed, char **map)
{
	int	row;

	row = 0;
	get_int_map_size(cubed, map);
	cubed->map.map = (int *)malloc(sizeof(int) * cubed->map.map_s);
	if (!cubed->map.map)
		error_exit(cubed, "MALLOC ERROR\n");
	while (map[row])
		fill_int_array(cubed, map[row++]);
}
