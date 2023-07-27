/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:05:22 by ekoljone          #+#    #+#             */
/*   Updated: 2023/07/27 18:32:05 by ekoljone         ###   ########.fr       */
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

	rows = get_row_size(filename);
	if (rows < 9)
		exit(1);
	array = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!array)
		exit(1);
	fill_array_with_contents(cubed, filename, array);
	return (array);
}

void	get_textures(t_cubed *cubed, char *row)
{
	char	**texture;

	if (ft_strnstr(row, "WE", SIZE_MAX))
}

void	get_attribute(t_cubed *cubed, char *row)
{
	
		
}

void	get_map_attributes(t_cubed *cubed, char **file)
{
	int	row;

	row = 0;
	while (file[row])
	{
		get_attribute(cubed, file[row++]);
	}
}

void	map_parsing(t_cubed *cubed, char *filename)
{
	char	**file;

	file = get_file_contents(cubed, filename);
}

int main(int argc, char **argv)
{
	t_cubed cubed;

	if (argc != 2)
		return (1);
	map_parsing(&cubed, argv[1]);
	return (0);
}
