/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:05:22 by ekoljone          #+#    #+#             */
/*   Updated: 2023/07/28 15:33:02 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_row_size(char *filename)
{
	int		counter;
	int		fd;
	char	*row;

	counter = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(1);
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

	(void)cubed;
	ctr = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(1);
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

	(void)cubed;
	rows = get_row_size(filename);
	if (rows < 9)
		exit(1);
	array = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!array)
		exit(1);
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

	(void)cubed;
	index = 0;
	while (row[index] && row[index] != '.')
		index++;
	path = ft_substr(row, index, ft_strlen(&row[index]) - 1);
	if (!path)
		exit(1);
	return (path);
}

void	get_textures(t_cubed *cubed, char *row)
{
	if (row[0] == 'W' && row[1] == 'E' && ft_is_white_space(row[2]))
	{
		if (cubed->map.path_to_west)
			exit (1);
		cubed->map.path_to_west = texture_path(cubed, row);
	}
	else if (row[0] == 'E' && row[1] == 'A' && ft_is_white_space(row[2]))
	{
		if (cubed->map.path_to_east)
			exit (1);
		cubed->map.path_to_east = texture_path(cubed, row);
	}
	else if (row[0] == 'S' && row[1] == 'O' && ft_is_white_space(row[2]))
	{
		if (cubed->map.path_to_south)
			exit (1);
		cubed->map.path_to_south = texture_path(cubed, row);
	}
	else if (row[0] == 'N' && row[1] == 'O' && ft_is_white_space(row[2]))
	{
		if (cubed->map.path_to_north)
			exit (1);
		cubed->map.path_to_north = texture_path(cubed, row);
	}
}

void	get_attribute(t_cubed *cubed, char *row)
{
	if (ft_strlen(row) <= 1)
		return ;
	get_textures(cubed, row);

}
int	check_if_map_started(char *row)
{
	int	index;

	index = 0;
	while (row[index])
	{
		if (ft_strlen(row) < 3 || (row[index] != '1' && !ft_is_white_space(row[index])))
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

int	get_map_size(char **file)
{
	int	row;
	int	size;

	row = iterate_to_map_start(file);
	size = 0;
	while (file[row])
	{
		row++;
		size++;
	}
	return (size);
}

void	get_map(t_cubed *cubed, char **file)
{
	int	row;
	int	map_row;
	int	size;

	row = iterate_to_map_start(file);
	size = get_map_size(file);
	map_row = 0;
	cubed->map.map = (char **)malloc(sizeof(char *) * size + 1);
	if (!cubed->map.map)
		exit (1);
	while (file[row])
	{
		cubed->map.map[map_row++] = ft_substr(file[row], 0, ft_strlen(file[row]) - 1);
		row++;
	}
	cubed->map.map[map_row] = 0;
}

void	get_map_attributes(t_cubed *cubed, char **file)
{
	int	row;

	row = 0;
	cubed->map.path_to_east = NULL;
	cubed->map.path_to_west = NULL;
	cubed->map.path_to_north = NULL;
	cubed->map.path_to_south = NULL;
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
		exit(1);
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
