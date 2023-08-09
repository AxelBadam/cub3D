/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:05:22 by ekoljone          #+#    #+#             */
/*   Updated: 2023/08/09 15:26:55 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define WIDTH 800
#define HEIGHT 600

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
		error_exit(cubed, "INVALID MAP\n");
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

void	check_row(t_cubed *cubed, char *row, int *spawn)
{
	int	index;

	index = 0;
	if (row[0] != '1' && row[ft_strlen(row) - 1] != '1')
	{
		printf("MORO\n");
		error_exit(cubed, "INVALID MAP\n");
	}
	while (row[index])
	{
		check_index_spot(cubed, row[index]);
		*spawn += check_direction(row[index++]);
	}
}

void check_map(t_cubed *cubed)
{
	int	row;
	int	spawn;

	spawn = 0;
	row = 0;
	while (cubed->map.map[row])
	{
		if (row == 0 || cubed->map.map[row + 1] == NULL)
			check_top_and_bottom(cubed, cubed->map.map[row]);
		else
			check_row(cubed, cubed->map.map[row], &spawn);
		row++;
	}
	if (spawn == 0 || spawn > 1)
		error_exit(cubed, "INVALID SPAWN\n");
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
	free_string_array(file);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_player(t_cubed *cubed)
{
	int	x;
	int	y;

	x = cubed->player.px;
	y = cubed->player.py;
	while(x < (cubed->player.px + 8))
	{
		while (y < (cubed->player.py + 8))
		{
			mlx_put_pixel(cubed->mlx.image, x, y, 0xFF00FFFF);
			y++;
		}
		y = cubed->player.py;
		x++;
	}
}

void	draw(t_cubed *cubed)
{
	if (cubed->mlx.image)
	{
		mlx_delete_image(cubed->mlx.mlx, cubed->mlx.image);
		cubed->mlx.image = NULL;
	}
	cubed->mlx.image = mlx_new_image(cubed->mlx.mlx, WIDTH, HEIGHT);
	draw_map(cubed);
	draw_player(cubed);
	if (mlx_image_to_window(cubed->mlx.mlx, cubed->mlx.image, 0, 0) == -1)
	{
		mlx_close_window(cubed->mlx.mlx);
		puts(mlx_strerror(mlx_errno));
		exit(69);
	}
}

void	rotate_player(t_cubed *cubed, int key)
{
	if (key == 'D')
		cubed->player.pa += 0.1;
	else
		cubed->player.pa -= 0.1;
	if (cubed->player.pa < 0)
	{
		cubed->player.pa += 2 * PI;
		cubed->player.dx = cos(cubed->player.pa) * 5;
		cubed->player.dy = sin(cubed->player.pa) * 5;
	}
	else if (cubed->player.pa > (2 * PI))
	{
		cubed->player.pa -= 2 * PI;
		cubed->player.dx = cos(cubed->player.pa) * 5;
		cubed->player.dy = sin(cubed->player.pa) * 5;
	}
	printf("PLAYER ANGLE == %f\n", cubed->player.pa);
}

void	move_player(t_cubed *cubed, int key)
{
	if (key == 'W')
	{
		cubed->player.px += cubed->player.dx;
		cubed->player.py += cubed->player.dy;
	}
	else
	{
		cubed->player.px -= cubed->player.dx;
		cubed->player.py -= cubed->player.dy;
	}
}

void my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_cubed *cubed;

	cubed = (t_cubed *)param;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		move_player(cubed, 'W');
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		move_player(cubed, 'S');
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		rotate_player(cubed, 'D');
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		rotate_player(cubed, 'A');
	draw(cubed);
}

int	map[] =
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

void	draw_rectangle(t_cubed *cubed, int ry, int rx, int color)
{
	int	x = 0;
	int y = ry;

	while (y < ry + HEIGHT / 8 - 1)
	{
		x = rx;
		while (x < rx + WIDTH / 8 - 1)
			mlx_put_pixel(cubed->mlx.image, x++, y, color);
		y++;
	}
}

void	draw_map(t_cubed *cubed)
{
	int	i = 0;
	int	x = 1;
	int y = 1;
	int color;
	
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (map[i] && map[i] == 1)
				color = 0xFFFFFFFF;
			else
				color = 0x000000FF;
			draw_rectangle(cubed, y, x, color);
			x += WIDTH / 8;
			i++;
		}
		x = 1;
		y += HEIGHT / 8;
	}
}

void	cub3d(t_cubed *cubed)
{
	cubed->player.px = 10;
	cubed->player.py = 10;
	cubed->player.pa = 0;
	cubed->player.dx = cos(cubed->player.pa) * 5;
	cubed->player.dy = sin(cubed->player.pa) * 5;
	cubed->mlx.image = NULL;
	cubed->mlx.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!(cubed->mlx.mlx))
	{
		puts(mlx_strerror(mlx_errno));
		exit(69);
	}
	cubed->mlx.image = mlx_new_image(cubed->mlx.mlx, WIDTH, HEIGHT);
	if (!(cubed->mlx.image))
	{
		mlx_close_window(cubed->mlx.mlx);
		puts(mlx_strerror(mlx_errno));
		exit(69);
	}
	draw(cubed);
	mlx_key_hook(cubed->mlx.mlx, &my_keyhook, cubed);
	mlx_loop(cubed->mlx.mlx);
	mlx_terminate(cubed->mlx.mlx);
}

int main(int argc, char **argv)
{
	t_cubed cubed;

	if (argc != 2)
		return (1);
	map_parsing(&cubed, argv[1]);
	cub3d(&cubed);
	return (0);
}
