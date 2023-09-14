/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:39:35 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/14 14:01:08 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**get_file_contents(t_cubed *cubed, char *filename)
{
	char	**array;
	int		fd;
	char	*row;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit(NULL, "INVALID FILENAME\n");
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

void	map_parsing(t_cubed *cubed, char *filename)
{
	char	**file;

	if (!check_file_name(filename))
		error_exit(NULL, "INVALID FILENAME\n");
	file = get_file_contents(cubed, filename);
	get_map_attributes(cubed, file);
	free_string_array(file);
}
