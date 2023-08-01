/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:05:22 by ekoljone          #+#    #+#             */
/*   Updated: 2023/08/01 17:52:56 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(t_cubed *cubed, char *error_msg)
{
	(void)cubed;
	perror(error_msg);
	exit(1);
}

int	get_row_size(char *filename)
{
	int		counter;
	int		fd;
	char	*row;

	counter = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit(NULL, "OPEN FAILED\n");
	while (1)
	{
		row = get_next_line(fd);
		if (!row)
			break;
		free(row);
		counter++;
	}
	close(fd);
	return (counter);
}

void	fill_array_with_contents(t_cubed *cubed, char *filename, char **array)
{
	int	fd;
	int	ctr;

	ctr = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit(cubed, "OPEN FAILED\n");
	while (1)
	{
		array[ctr++] = get_next_line(fd);
		if (!array[ctr - 1])
			break ;
	}
	close(fd);
}

char	**get_file_contents(t_cubed *cubed, char *filename)
{
	char	**array;
	int		rows;

	rows = get_row_size(filename);
	if (rows < 9)
		error_exit(cubed, "INVALID MAP\n");
	array = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!array)
		error_exit(cubed, "MALLOC ERROR\n");
	fill_array_with_contents(cubed, filename, array);
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
	while (row[index] && row[index] != '.')
		index++;
	path = ft_substr(row, index, ft_strlen(&row[index]) - 1);
	if (!path)
		error_exit(cubed, "MALLOC ERROR\n");
	return (path);
}

void	get_textures(t_cubed *cubed, char *row)
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
	else if (row[0] == 'S' && row[1] == 'O' && ft_is_white_space(row[2]))
	{
		if (cubed->map.path_to_south)
			error_exit(cubed, "TOO MANY PATHS\n");
		cubed->map.path_to_south = texture_path(cubed, row);
	}
	else if (row[0] == 'N' && row[1] == 'O' && ft_is_white_space(row[2]))
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
		return (-1);
	color = ft_atoi(array[0]) * pow(256, 2) + ft_atoi(array[1]) * 256 + ft_atoi(array[2]);
	return (color);
}

void	get_colors(t_cubed *cubed, char *row)
{
	if (row[0] == 'F' && ft_is_white_space(row[1]))
	{
		if (cubed->map.floor_color != -1)
			error_exit(cubed, "TOO MANY COLORS\n");
		cubed->map.floor_color = get_color(row);
	}
	else if (row[0] == 'C' && ft_is_white_space(row[1]))
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

void	get_map(t_cubed *cubed, char **file)
{
	int	row;
	int	map_row;
	int	size;

	row = iterate_to_map_start(file);
	size = get_map_size(file);
	if (size < 3)
		exit (100);
	map_row = 0;
	cubed->map.map = (char **)malloc(sizeof(char *) * size + 1);
	if (!cubed->map.map)
		error_exit(cubed, "MALLOC ERROR\n");
	while (file[row] && !check_for_empty_row(file[row]))
	{
		cubed->map.map[map_row++] = ft_substr(file[row], 0, iterate_to_newline(file[row]));
		row++;
	}
	cubed->map.map[map_row] = 0;
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
	(void)cubed;
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

void	check_row(t_cubed *cubed, char *row)
{
	int	index;
	int	spawn;

	spawn = 0;
	index = 0;
	if (row[0] != '1' || row[ft_strlen(row) - 1] != '1')
		error_exit(cubed, "INVALID MAP\n");
	while (row[index])
	{
		check_index_spot(cubed, row[index]);
		spawn += check_direction(row[index++]);
	}
	if (spawn == 0 || spawn > 1)
		error_exit(cubed, "INVALID SPAWN\n");
}

void check_map(t_cubed *cubed)
{
	int	direction;
	int	row;

	row = 0;
	direction = 0;
	while (cubed->map.map[row])
	{
		if (row == 0 || cubed->map.map[row + 1] == NULL)
			check_top_and_bottom(cubed, cubed->map.map[row]);
		else
			check_row(cubed, cubed->map.map[row]);
		row++;
	}
}

void	check_for_invalid_attributes(t_cubed *cubed)
{
	if (!cubed->map.path_to_east || !cubed->map.path_to_west
		|| !cubed->map.path_to_north || !cubed->map.path_to_south)
		error_exit(cubed, "PATH ERROR\n");
	if (cubed->map.cealing_color == -1 || cubed->map.floor_color == -1)
		error_exit(cubed, "COLOR ERROR\n");
	check_map(cubed);
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
}

void	get_map_attributes(t_cubed *cubed, char **file)
{
	int	row;

	row = 0;
	nullify_map(cubed);
	get_map(cubed, file);
	while (file[row])
	{
		if (check_if_map_started(file[row]))
			break ;
		get_attribute(cubed, file[row++]);
	}
	row = 0;
	while (cubed->map.map[row])
		printf("%s\n", cubed->map.map[row++]);
	printf("cealing %li\nfloor %li\n", cubed->map.cealing_color, cubed->map.floor_color);
	check_for_invalid_attributes(cubed);
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
}

int main(int argc, char **argv)
{
	t_cubed cubed;

	if (argc != 2)
		return (1);
	map_parsing(&cubed, argv[1]);
	return (0);
}
