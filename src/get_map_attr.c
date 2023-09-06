/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_attr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:15:42 by ekoljone          #+#    #+#             */
/*   Updated: 2023/09/06 11:59:27 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_attributes(t_cubed *cubed, char **file)
{
	int		row;
	char	**map;

	row = 0;
	nullify_map(cubed);
	map = get_map(cubed, file);
	while (file[row])
	{
		if (check_if_map_started(file[row]))
			break ;
		get_attribute(cubed, file[row++]);
	}
	row = 0;
	check_for_invalid_attributes(cubed, map);
	convert_map_to_int(cubed, map);
	free_string_array(map);
}

void	get_attribute(t_cubed *cubed, char *row)
{
	if (ft_strlen(row) < 1)
		return ;
	get_textures(cubed, row);
	get_colors(cubed, row);
}

int	get_color(t_cubed *cubed, char *row)
{
	int			index;
	int			color;
	char		**array;

	index = 0;
	while (row[index] && !ft_isdigit(row[index]))
		index++;
	array = ft_split(&row[index], ',');
	if (get_2d_array_size(array) != 3)
	{
		free_string_array(array);
		error_exit(cubed, "COLOR ERROR\n");
	}
	color = get_rgba(ft_atoi(array[0]),
			ft_atoi(array[1]), ft_atoi(array[2]), 255);
	free_string_array(array);
	return (color);
}

void	get_colors(t_cubed *cubed, char *row)
{
	int	ctr;

	ctr = iterate_over_white_spaces(row);
	if (row[ctr] == 'F' && ft_is_white_space(row[ctr + 1]))
	{
		if (cubed->map.f_color_check)
			error_exit(cubed, "TOO MANY COLORS\n");
		cubed->map.floor_color = get_color(cubed, row);
		cubed->map.f_color_check = 1;
	}
	else if (row[ctr] == 'C' && ft_is_white_space(row[ctr + 1]))
	{
		if (cubed->map.c_color_check)
			error_exit(cubed, "TOO MANY COLORS\n");
		cubed->map.cealing_color = get_color(cubed, row);
		cubed->map.c_color_check = 1;
	}
}

void	get_textures(t_cubed *cubed, char *row)
{
	int	ctr;

	ctr = iterate_over_white_spaces(row);
	check_if_east_or_west(cubed, &row[ctr]);
	if (row[ctr] == 'S' && row[ctr + 1] == 'O'
		&& ft_is_white_space(row[ctr + 2]))
	{
		if (cubed->map.path_to_south)
			error_exit(cubed, "TOO MANY PATHS\n");
		cubed->map.path_to_south = texture_path(cubed, row);
	}
	else if (row[ctr] == 'N' && row[ctr + 1] == 'O'
		&& ft_is_white_space(row[ctr + 2]))
	{
		if (cubed->map.path_to_north)
			error_exit(cubed, "TOO MANY PATHS\n");
		cubed->map.path_to_north = texture_path(cubed, row);
	}
}
