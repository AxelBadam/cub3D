/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:39:35 by atuliara          #+#    #+#             */
/*   Updated: 2023/08/24 15:55:48 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**append_2d(char **twod, char *str_to_add)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (get_2d_array_size(twod) + 2));
	if (!new)
		return (NULL);
	i = 0;
	if (twod)
	{
		while (twod[i])
		{
			new[i] = ft_strdup(twod[i]);
			if (!new[i])
				return (NULL);
			i++;
		}
	}
	new[i] = ft_strdup(str_to_add);
	if (!new[i])
		return (NULL);
	new[++i] = 0;
	free_string_array(twod);
	return (new);
}

void	free_string_array(char **array)
{
	int	ctr;

	ctr = 0;
	if (array)
	{
		while (array[ctr])
			free(array[ctr++]);
		free(array);
		array = NULL;
	}
}

void	error_exit(t_cubed *cubed, char *error_msg)
{
	(void)cubed;
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_msg, 2);
	exit(1);
}

char	**get_file_contents(t_cubed *cubed, char *filename)
{
	char	**array;
	int		fd;
	char	*row;

	fd = open(filename, O_RDONLY);
	array = NULL;
	while (1)
	{
		row = get_next_line(fd);
		if (!row)
			break ;
		array = append_2d(array, row);
		free(row);
		if (!array)
			error_exit(cubed, "MALLOC ERROR\n");
	}
	close(fd);
	return (array);
}

int	ft_is_white_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*texture_path(t_cubed *cubed, char *row)
{
	int		index;
	char	*path;

	index = 0;
	while (row[index] && row[index] != '.' && row[index] != '/')
		index++;
	path = ft_substr(row, index, ft_strlen(&row[index]) - 1);
	if (!path)
		error_exit(cubed, "MALLOC ERROR\n");
	return (path);
}

int	iterate_over_white_spaces(char *row)
{
	int	ctr;

	ctr = 0;
	while (row[ctr] && ft_is_white_space(row[ctr]))
		ctr++;
	return (ctr);
}

void	check_if_east_or_west(t_cubed *cubed, char *row)
{
	if (row[0] == 'W' && row[1] == 'E' && ft_is_white_space(row[2]))
	{
		if (cubed->map.path_to_west)
			error_exit(cubed, "TOO MANY PATHS\n");
		cubed->map.path_to_west = texture_path(cubed, row);
	}
	else if (row[0] == 'E' && row[1] == 'A' && ft_is_white_space(row[2]))
	{
		if (cubed->map.path_to_east)
			error_exit(cubed, "TOO MANY PATHS\n");
		cubed->map.path_to_east = texture_path(cubed, row);
	}
}

void	get_textures(t_cubed *cubed, char *row)
{
	int	ctr;

	ctr = iterate_over_white_spaces(row);
	check_if_east_or_west(cubed, &row[ctr]);
	if (row[ctr] == 'S' && row[ctr + 1] == 'O' && ft_is_white_space(row[ctr + 2]))
	{
		if (cubed->map.path_to_south)
			error_exit(cubed, "TOO MANY PATHS\n");
		cubed->map.path_to_south = texture_path(cubed, row);
	}
	else if (row[ctr] == 'N' && row[ctr + 1] == 'O' && ft_is_white_space(row[ctr + 2]))
	{
		if (cubed->map.path_to_north)
			error_exit(cubed, "TOO MANY PATHS\n");
		cubed->map.path_to_north = texture_path(cubed, row);
	}
}
int	get_2d_array_size(char **array)
{
	int	size;

	size = 0;
	if (array)
	{
		while (array[size])
			size++;
	}
	return (size);
}

long int	get_color(char *row)
{
	int			index;
	long int	color;
	char		**array;

	index = 0;
	while (row[index] && !ft_isdigit(row[index]))
		index++;
	array = ft_split(&row[index], ',');
	if (get_2d_array_size(array) != 3)
	{
		free_string_array(array);
		return (-1);
	}
	color = ft_atoi(array[0]) * pow(256, 2) + ft_atoi(array[1]) * 256 + ft_atoi(array[2]);
	free_string_array(array);
	return (color);
}

void	get_colors(t_cubed *cubed, char *row)
{
	int	ctr;

	ctr = iterate_over_white_spaces(row);
	if (row[ctr] == 'F' && ft_is_white_space(row[ctr + 1]))
	{
		if (cubed->map.floor_color != -1)
			error_exit(cubed, "TOO MANY COLORS\n");
		cubed->map.floor_color = get_color(row);
	}
	else if (row[ctr] == 'C' && ft_is_white_space(row[ctr + 1]))
	{
		if (cubed->map.cealing_color != -1)
			error_exit(cubed, "TOO MANY COLORS\n");
		cubed->map.cealing_color = get_color(row);
	}
}

void	get_attribute(t_cubed *cubed, char *row)
{
	if (ft_strlen(row) < 1)
		return ;
	get_textures(cubed, row);
	get_colors(cubed, row);
}
int	check_if_map_started(char *row)
{
	int	index;

	index = 0;
	while (row[index])
	{
		if (!ft_strchr(row, '1') || (row[index] != '1' && !ft_is_white_space(row[index])))
			return (0);
		index++;
	}
	return (1);
}

int	iterate_to_map_start(char **file)
{
	int row;

	row = 0;
	while (file[row])
	{
		if (check_if_map_started(file[row]))
			break ;
		row++;
	}
	return (row);
}

int	check_for_empty_row(char *row)
{
	int	index;

	index = 0;
	while (row[index])
	{
		if (!ft_is_white_space(row[index++]))
			return (0);
	}
	return (1);
}

int	get_map_size(char **file)
{
	int	row;
	int	size;

	row = iterate_to_map_start(file);
	size = 0;
	while (file[row] && !check_for_empty_row(file[row]))
	{
		row++;
		size++;
	}
	while (file[row])
	{
		if (!check_for_empty_row(file[row++]))
			return (0);
	}
	return (size);
}

int	iterate_to_newline(char *row)
{
	int	ctr;

	ctr = 0;
	while (row[ctr] && row[ctr] != '\n')
		ctr++;
	return (ctr);
}

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
	cubed->map.mapS = size * row;
	cubed->map.mapY = row;
	cubed->map.mapX = size;
}

void	get_player_angle(t_cubed *cubed, char direction)
{
	if (direction == 'W')
		cubed->player.pa = 180;
	else if (direction == 'E')
		cubed->player.pa = 0;
	else if (direction == 'S')
		cubed->player.pa = 270;
	else if (direction == 'N')
		cubed->player.pa = 90;
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
		if (ft_is_white_space(row[column]))
			cubed->map.map[index] = 2;
		else if (row[column] == 'W' || row[column] == 'S' || row[column] == 'E' || row[column] == 'N')
		{
			get_player_angle(cubed, row[column]);
			cubed->map.map[index] = 3;
		}
		else
			cubed->map.map[index] = row[column] - 48;
		index++;
		column++;
		if (!row[column] && cubed->map.mapX > column)
		{
			tmp = column;
			while (tmp < cubed->map.mapX)
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
	int	index;
	int	column;

	column = 0;
	row = 0;
	index = 0;
	get_int_map_size(cubed, map);
	cubed->map.map = (int *)malloc(sizeof(int) * cubed->map.mapS);
	if (!cubed->map.map)
		error_exit(cubed, "MALLOC ERROR\n");
	while (map[row])
		fill_int_array(cubed, map[row++]);
	for (int i = 0; i < cubed->map.mapS; i++)
		printf("%i", cubed->map.map[i]);
}

char	**get_map(t_cubed *cubed, char **file)
{
	int		row;
	char	**map;
	int		map_row;
	int		size;

	row = iterate_to_map_start(file);
	size = get_map_size(file);
	if (size < 3)
		error_exit(cubed, "INVALID MAP\n");
	map_row = 0;
	map = (char **)malloc(sizeof(char *) * size + 1);
	if (!map)
		error_exit(cubed, "MALLOC ERROR\n");
	while (file[row] && !check_for_empty_row(file[row]))
	{
		map[map_row++] = ft_substr(file[row], 0, iterate_to_newline(file[row]));
		if (!map[map_row - 1])
			error_exit(cubed, "MALLOC ERROR\n");
		row++;
	}
	map[map_row] = 0;
	return (map);
}

void	check_top_and_bottom(t_cubed *cubed, char *row)
{
	int	index;

	index = 0;
	while (row[index])
	{
		if (!ft_is_white_space(row[index]) && row[index] != '1')
			error_exit(cubed, "INVALID MAP\n");
		index++;
	}
}

void	check_index_spot(t_cubed *cubed, char index)
{
	if (index != '1' && index != '0'
		&& index != 'W' && index != 'E'
		&& index != 'S' && index != 'N'
		&& !ft_is_white_space(index))
		error_exit(cubed, "INVALID MAP\n");
}

int	check_direction(char index)
{
	if (index == 'W' ||	index == 'S'
		|| index == 'E' || index == 'N')
		return (1);
	return (0);
}

int	check_wall(char *row, char *next_row, int *wall)
{
	int	ctr;

	ctr = 0;
	while (row[ctr] && (row[ctr] == '1' || ft_is_white_space(row[ctr]) || check_direction(row[ctr])))
	{
		if (next_row[ctr] && row[ctr] == '1' && next_row[ctr] == '1')
			*wall = 1;
		if (next_row[ctr] == '0')
			break ;
		ctr++;
	}
	return (ctr);
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
	while ((row[ctr] && (row[ctr] == '0' || row[ctr] == '1' || ft_is_white_space(row[ctr]) || check_direction(row[ctr]))))
	{
		if (row[ctr] == '1' && !ft_strchr(&row[ctr], '0') && !ft_strchr(&next_row[ctr], '0'))
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

void check_map(t_cubed *cubed, char **map)
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

void	check_for_invalid_attributes(t_cubed *cubed, char **map)
{
	if (!cubed->map.path_to_east || !cubed->map.path_to_west
		|| !cubed->map.path_to_north || !cubed->map.path_to_south)
		error_exit(cubed, "PATH ERROR\n");
	if (cubed->map.cealing_color == -1 || cubed->map.floor_color == -1)
		error_exit(cubed, "COLOR ERROR\n");
	check_map(cubed, map);
}

void	nullify_map(t_cubed *cubed)
{
	cubed->map.path_to_east = NULL;
	cubed->map.path_to_west = NULL;
	cubed->map.path_to_north = NULL;
	cubed->map.path_to_south = NULL;
	cubed->map.map = NULL;
	cubed->map.cealing_color = -1;
	cubed->map.floor_color = -1;
	cubed->map.map_postionX = 0;
	cubed->map.map_postionY = 0;
}

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
	printf("cealing %li\nfloor %li\n", cubed->map.cealing_color, cubed->map.floor_color);
	check_for_invalid_attributes(cubed, map);
	convert_map_to_int(cubed, map);
	free_string_array(map);
}

int	check_file_name(char *filename)
{
	int	index;

	index = 0;
	while (filename[index] && filename[index] != '.')
		index++;
	if (ft_strncmp(&filename[index], ".cub", SIZE_MAX) != 0)
		return (0);
	return (1);
}

void	map_parsing(t_cubed *cubed, char *filename)
{
	char	**file;

	if (!check_file_name(filename))
		error_exit(cubed, "INVALID FILENAME\n");
	file = get_file_contents(cubed, filename);
	get_map_attributes(cubed, file);
	free_string_array(file);
}
