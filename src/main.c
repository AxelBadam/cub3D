/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:05:22 by ekoljone          #+#    #+#             */
/*   Updated: 2023/08/23 17:26:19 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(mlx_image_t *image, int x, int y, int color)
{
	if (y < HEIGHT && y >= 0 && x < WIDTH && x >= 0)
		mlx_put_pixel(image, x, y, color);
}

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


void	plotline(t_cubed *cubed, t_vec v1, t_vec v2)
{
	cubed->bres.dx = abs(v2.x - v1.x);
	cubed->bres.dy = -abs(v2.y - v1.y);
	cubed->bres.sx = -1;
	if (v1.x < v2.x)
		cubed->bres.sx = 1;
	cubed->bres.sy = -1;
	if (v1.y < v2.y)
		cubed->bres.sy = 1;
	cubed->bres.error[0] = cubed->bres.dx + cubed->bres.dy;
	while (v1.x != v2.x || v1.y != v2.y)
	{
		my_pixel_put(cubed->mlx.image, v1.x, v1.y, v1.color);
		cubed->bres.error[1] = 2 * cubed->bres.error[0];
		if (cubed->bres.error[1] >= cubed->bres.dy)
		{
			cubed->bres.error[0] += cubed->bres.dy;
			v1.x += cubed->bres.sx;
		}
		if (cubed->bres.error[1] <= cubed->bres.dx)
		{
			cubed->bres.error[0] += cubed->bres.dx;
			v1.y += cubed->bres.sy;
		}
	}
	my_pixel_put(cubed->mlx.image, v1.x, v1.y, v1.color);
}

float degToRad(int a) { return a*M_PI/180.0;}
float FixAng(float a)
{
	if(a > 359)
		a -= 360;
 	if(a < 0)
 		a += 360;
 	return a;
}
float distance(ax,ay,bx,by,ang){ return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);}

static uint32_t	*get_text_color(mlx_texture_t *texture)
{
	int				i;
	unsigned int	pos;
	uint8_t			rgb[4];
	uint32_t		*colors;

	i = 0;
	colors = malloc(sizeof(uint32_t) * (texture->width + 1)
			* (texture->height + 1));
	if (colors == NULL)
		printf("yo");
	pos = 0;
	while (pos < texture->width * texture->height * texture->bytes_per_pixel)
	{
		rgb[0] = texture->pixels[pos];
		rgb[1] = texture->pixels[pos + 1];
		rgb[2] = texture->pixels[pos + 2];
		rgb[3] = texture->pixels[pos + 3];
		colors[i] = (rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + rgb[3];
		pos += texture->bytes_per_pixel;
		i++;
	}
	return (colors);
}

void	ray_plotline(t_cubed *cubed, t_vec v1, t_vec v2)
{
	cubed->bres.dx = abs(v2.x - v1.x);
	cubed->bres.dy = -abs(v2.y - v1.y);
	cubed->bres.sx = -1;
	if (v1.x < v2.x)
		cubed->bres.sx = 1;
	cubed->bres.sy = -1;
	if (v1.y < v2.y)
		cubed->bres.sy = 1;
	cubed->bres.error[0] = cubed->bres.dx + cubed->bres.dy;
	while (v1.x != v2.x || v1.y != v2.y)
	{
		if (v1.x > 3 && v1.x < 153 && v1.y > 3 && v1.y < 154)
			my_pixel_put(cubed->mlx.image, v1.x, v1.y, v1.color);
		cubed->bres.error[1] = 2 * cubed->bres.error[0];
		if (cubed->bres.error[1] >= cubed->bres.dy)
		{
			cubed->bres.error[0] += cubed->bres.dy;
			v1.x += cubed->bres.sx;
		}
		if (cubed->bres.error[1] <= cubed->bres.dx)
		{
			cubed->bres.error[0] += cubed->bres.dx;
			v1.y += cubed->bres.sy;
		}
	}
}

void drawRays2D(t_cubed *cubed)
{
	t_ray ray;
	
	ray.ra=FixAng(cubed->player.pa+30);                                                      //ray set back 30 degrees
	ray.r = -1;
	while(++ray.r < 120)
	{
				//---Vertical--- 
		ray.dof = 0;
		ray.side = 0;
		ray.disV = 100000;
		ray.Tan = tan(degToRad(ray.ra));
		
		if(cos(degToRad(ray.ra)) > 0.001)
		{
			ray.rx = (((int)cubed->player.px / cubed->map.mapS) * cubed->map.mapS) + cubed->map.mapS;
			ray.ry = (cubed->player.px-ray.rx) * ray.Tan + cubed->player.py;
			ray.xo = cubed->map.mapS;
			ray.yo = -ray.xo * ray.Tan;
		}//looking left
		else if (cos(degToRad(ray.ra)) < -0.001)
		{
			ray.rx = (((int)cubed->player.px / cubed->map.mapS) * cubed->map.mapS) -0.0001;
			ray.ry = (cubed->player.px-ray.rx) * ray.Tan+cubed->player.py;
			ray.xo = -cubed->map.mapS;
			ray.yo = -ray.xo * ray.Tan;
		}//looking right
		else
		{
			ray.rx = cubed->player.px;
			ray.ry = cubed->player.py;
			ray.dof = cubed->map.mapX;
		}                                                  //looking up or down. no hit  
		
	while(ray.dof < cubed->map.mapX) 
	{ 
		ray.mx = (int)(ray.rx) / cubed->map.mapS;
		ray.my = (int)(ray.ry) / cubed->map.mapS;
		ray.mp = ray.my * cubed->map.mapX + ray.mx;
		if(ray.mp > 0 && ray.mp < cubed->map.mapX * cubed->map.mapY && cubed->map.map[ray.mp] == 1)
		{
			ray.dof = cubed->map.mapX;
			ray.disV = cos(degToRad(ray.ra)) * (ray.rx-cubed->player.px) - sin(degToRad(ray.ra)) * (ray.ry-cubed->player.py);
		}//hit      
		else
		{
			ray.rx += ray.xo;
			ray.ry += ray.yo;
			ray.dof += 1;
		}                                               //check next horizontal
	} 
	ray.vx=ray.rx; 
	ray.vy=ray.ry;
	//---Horizontal---
	ray.dof = 0;
	ray.disH = 100000;
	ray.Tan = 1.0 / ray.Tan; 
	if (sin(degToRad(ray.ra)) > 0.001)
	{
		ray.ry = (((int)cubed->player.py / cubed->map.mapS) * cubed->map.mapS) - 0.0001; //testi
		ray.rx = (cubed->player.py-ray.ry) * ray.Tan + cubed->player.px;
		ray.yo = -cubed->map.mapS;
		ray.xo = -ray.yo * ray.Tan;
	}//looking up
	else if (sin(degToRad(ray.ra)) < -0.001)
	{
		ray.ry = (((int)cubed->player.py / cubed->map.mapS) * cubed->map.mapS) + cubed->map.mapS;
		ray.rx = (cubed->player.py-ray.ry) * ray.Tan+cubed->player.px;
		ray.yo = cubed->map.mapS;
		ray.xo = -ray.yo * ray.Tan;
	}//looking down
	else
	{
		ray.rx = cubed->player.px;
		ray.ry = cubed->player.py;
		ray.dof = cubed->map.mapY;
	}                                                   //looking straight left or right
	while (ray.dof < cubed->map.mapY) 
	{ 
		ray.mx = (int)(ray.rx) / cubed->map.mapS;
		ray.my = (int)(ray.ry) / cubed->map.mapS;
		ray.mp = ray.my * cubed->map.mapX + ray.mx;
		if(ray.mp > 0 && ray.mp < cubed->map.mapX * cubed->map.mapY && cubed->map.map[ray.mp] == 1)
		{
			ray.dof = cubed->map.mapY;
			ray.disH = cos(degToRad(ray.ra)) * (ray.rx - cubed->player.px) - sin(degToRad(ray.ra)) * (ray.ry-cubed->player.py);
		}//hit         
		else
		{
			ray.rx+=ray.xo;
			ray.ry+=ray.yo;
			ray.dof+=1;
		}                                               //check next horizontal
	}
	
	float shade = 1;
	mlx_texture_t *text = NULL;
	if (ray.disV >= ray.disH)
	{
		if (ray.ra < 360 && ray.ra > 180)
			text = cubed->south;
		else if (ray.ra > 0 && ray.ra < 180)
			text = cubed->north;
	}
	if(!text && ray.disV <= ray.disH)  //horizontal hit first
	{ 
		shade = 0.5;
		ray.rx = ray.vx; 
		ray.ry = ray.vy; 
		ray.disH = ray.disV;
		if (ray.ra < 270 && ray.ra > 90)
			text = cubed->west;
		else if (ray.ra > 270 || ray.ra < 90)
			text = cubed->east;
	}

	//float	dist_traveledX = cubed->player.px - cubed->player.og_x;
	//float	dist_traveledY = cubed->player.py - cubed->player.og_y;

	//ray.rx = (ray.rx - dist_traveledX) - (cubed->player.og_x - (float)75);
	//ray.ry = (ray.ry - dist_traveledY) - (cubed->player.og_y - (float)75);
	//ray_plotline(cubed, (t_vec){(cubed->player.px + 3 - dist_traveledX) - (cubed->player.og_x - 75), (cubed->player.py + 3 - dist_traveledY) - (cubed->player.og_y - 75), 0, 0xFF0000FF}, (t_vec){ray.rx, ray.ry, 0, 0xFF0000FF});
	
	int ca = FixAng(cubed->player.pa-ray.ra);
    ray.disH = ray.disH * cos(degToRad(ca));                           //fix fisheye 
    int lineH = (cubed->map.mapS * HEIGHT) / (ray.disH);
    float ty_step = 32.0/(float)lineH;
    float ty_off = 0;
    if (lineH > HEIGHT)
    {
        ty_off = (lineH - HEIGHT)/ 2.0;
        lineH = HEIGHT;                                                     //line height and limit
    }
    int lineOff = HEIGHT / 2 - (lineH>>1);  //line offset

             //DRAW WALLS
    float ty=ty_off*ty_step;
    float tx;

	
	if (shade == 1) // flip textures in walls
	{
		tx = (int)(ray.rx/2.0) % 32;
		if (ray.ra > 180)
			tx = 31 - tx;
	}
	else
	{
		tx = (int)(ray.ry/2.0) % 32;
		if ( (ray.ra > 90 && ray.ra < 270))
			tx = 31 - tx;
	}

	int y;
	int x;
	
	u_int32_t *col = get_text_color(text);
	int pixel = (int)ty * 32 + (int)tx;

	for (y = 0; y < lineH; y++)
	{
		for (int yy = 0; yy <= 8; yy++)
		{
		for (x=0; x <= 8; x++)
		{
			pixel = (int)ty * 32 + (int)tx;
			//plotline(cubed, (t_vec){ray.r*20, lineOff, 0, 0xFF0000FF}, (t_vec){ray.r*20, lineOff+lineH, 0, col[pixel]});			
			my_pixel_put(cubed->mlx.image, ray.r*8+x, y+lineOff + yy, col[pixel]);
		}
		}
		ty+=ty_step;
	}
	ray.ra=FixAng(ray.ra - 0.5);                                                        //go to next ray, 60 total
	}
}

void	draw_player(t_cubed *cubed)
{
	int	x;
	int	y;

	x = 75;
	y = 75;
	while(x < (75 + 4))
	{
		while (y < (75 + 4))
		{
			my_pixel_put(cubed->mlx.image, x, y, 0xFF00FFFF);
			y++;
		}
		y = 75;
		x++;
	}
}
void	find_player_position(t_cubed *cubed)
{
	int	i = 0;
	int	x = 0;
	int y = 0;
	int xo = 0;
	int yo = 0;
	
	while (y < cubed->map.mapY)
	{
		while (x < cubed->map.mapX)
		{
			xo = x * cubed->map.mapS;
			yo = y * cubed->map.mapS;
			if (cubed->map.map[y * cubed->map.mapX + x] == 3)
			{
				cubed->player.px = xo + cubed->map.mapS / 2;
				cubed->player.py = yo + cubed->map.mapS / 2;
				cubed->player.og_x = xo + cubed->map.mapS / 2;
				cubed->player.og_y = yo + cubed->map.mapS / 2;
				cubed->map.map[y * cubed->map.mapX + x] = 0;
			}
			x++;
			i++;
		}
		x = 0;
		y++;
	}
}

void	draw_background(mlx_image_t *img)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(img, x, y, 0xFF0080FF);
			else
				mlx_put_pixel(img, x, y, 0xFF0800FF);
			x++;
		}
		x = 0;
		y++;
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
	draw_background(cubed->mlx.image);
	draw_map(cubed);
	drawRays2D(cubed);
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
	if (key == MLX_KEY_RIGHT)
		cubed->player.pa -= 5;
	else
		cubed->player.pa += 5;
	cubed->player.pa=FixAng(cubed->player.pa);
	cubed->player.dx=cos(degToRad(cubed->player.pa));
	cubed->player.dy=-sin(degToRad(cubed->player.pa));
}

void	move_player(t_cubed *cubed, int key)
{
	float perpendicular_dx;
	float perpendicular_dy;
	int xo = 0;
	int yo = 0;
	
	if(cubed->player.dx < 0)
	{
		xo = -(cubed->map.mapS / 4);
	}
	else
	{
		xo = cubed->map.mapS / 4;
	}                                    //x offset to check map
	if (cubed->player.dy < 0)
	{
		yo = -(cubed->map.mapS / 4);
	}
	else
	{
		yo = cubed->map.mapS / 4;
	}

	int ipx=cubed->player.px/cubed->map.mapS; int ipx_add_xo=(cubed->player.px+xo)/cubed->map.mapS; int ipx_sub_xo=(cubed->player.px-xo)/cubed->map.mapS;             //x position and offset
 	int ipy=cubed->player.py/cubed->map.mapS; int ipy_add_yo=(cubed->player.py+yo)/cubed->map.mapS; int ipy_sub_yo=(cubed->player.py-yo)/cubed->map.mapS; 
	if (key == 'W')
	{
		if(cubed->map.map[ipy * cubed->map.mapX + ipx_add_xo]==0)
		{
			cubed->player.px += cubed->player.dx * (cubed->map.mapS / 4);
			cubed->map.map_postionX -= cubed->player.dx * (cubed->map.mapS / 4);
		}
  		if(cubed->map.map[ipy_add_yo * cubed->map.mapX + ipx]==0)
		{
			cubed->player.py += cubed->player.dy * (cubed->map.mapS / 4);
			cubed->map.map_postionY -= cubed->player.dy * (cubed->map.mapS / 4);
		}
	}
	else if (key == 'S')
	{
		if(cubed->map.map[ipy * cubed->map.mapX + ipx_sub_xo]==0)
		{
			cubed->player.px -= cubed->player.dx * (cubed->map.mapS / 4);
			cubed->map.map_postionX += cubed->player.dx * (cubed->map.mapS / 4);
		}
  		if(cubed->map.map[ipy_sub_yo * cubed->map.mapX + ipx] == 0)
		{
			cubed->player.py -= cubed->player.dy * (cubed->map.mapS / 4);
			cubed->map.map_postionY +=cubed->player.dy * (cubed->map.mapS / 4);
		}
	}
	else if (key == 'D') 
	{
		perpendicular_dx = -cubed->player.dy;
    	perpendicular_dy = cubed->player.dx;
    	cubed->player.px += perpendicular_dx * cubed->map.mapS / 4;
    	cubed->player.py += perpendicular_dy * cubed->map.mapS / 4;
		cubed->map.map_postionX -= perpendicular_dx * cubed->map.mapS / 4;
		cubed->map.map_postionY -= perpendicular_dy * cubed->map.mapS / 4;
	} 
	else if (key == 'A') 
	{
   		perpendicular_dx = cubed->player.dy;
   		perpendicular_dy = -cubed->player.dx;
   		cubed->player.px += perpendicular_dx * cubed->map.mapS / 4;
		cubed->player.py += perpendicular_dy * cubed->map.mapS / 4;
		cubed->map.map_postionX -= perpendicular_dx * cubed->map.mapS / 4;
		cubed->map.map_postionY -= perpendicular_dy * cubed->map.mapS / 4;
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
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		move_player(cubed, 'A');
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		move_player(cubed, 'D');
	if (keydata.key ==  MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		rotate_player(cubed, MLX_KEY_RIGHT);
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		rotate_player(cubed, MLX_KEY_LEFT);
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		exit (0);
	draw(cubed);
}

void	draw_rectangle(t_cubed *cubed, int ry, int rx, int color)
{
	int	x = 0;
	int y = ry;

	while (y < ry + cubed->map.mapS)
	{
		x = rx;
		while (x < rx + cubed->map.mapS)
		{
			if (y > 3 && y < 153 && x > 3 && x < 153)
				my_pixel_put(cubed->mlx.image, x, y, color);
			x++;
		}
		y++;
	}
}
void	draw_map(t_cubed *cubed)
{
	int	i = 0;
	int	x = 0;
	int y = 0;
	int xo = 0;
	int yo = 0;
	int color;
	while (y < cubed->map.mapY)
	{
		while (x < cubed->map.mapX)
		{
			if (cubed->map.map[y * cubed->map.mapX + x] == 1)
				color = 0xFFFFFFFF;
			else
				color = 0x000000FF;
			xo = x * cubed->map.mapS + cubed->map.map_postionX;
			yo = y * cubed->map.mapS + cubed->map.map_postionY;
			draw_rectangle(cubed, yo - (cubed->player.og_y - 75), xo - (cubed->player.og_x - 75), color);
			x++;
			i++;
		}
		x = 0;
		y++;
	}
	plotline(cubed, (t_vec){3, 3, 0, 0xFF00FFFF}, (t_vec){3, 153, 0, 0xFF00FFFF});
	plotline(cubed, (t_vec){3, 153, 0, 0xFF00FFFF}, (t_vec){153, 153, 0, 0xFF00FFFF});
	plotline(cubed, (t_vec){153, 153, 0, 0xFF00FFFF}, (t_vec){153, 3, 0, 0xFF00FFFF});
	plotline(cubed, (t_vec){153, 3, 0, 0xFF00FFFF}, (t_vec){3, 3, 0, 0xFF00FFFF});
}

void load_text(t_cubed *cubed)
{
	cubed->north = mlx_load_png(cubed->map.path_to_north);
	cubed->south = mlx_load_png(cubed->map.path_to_south);
	cubed->east = mlx_load_png(cubed->map.path_to_east);
	cubed->west = mlx_load_png(cubed->map.path_to_west);
}

void	cub3d(t_cubed *cubed)
{
	cubed->map.mapS = 24;
	find_player_position(cubed);
	cubed->player.dx = cos(degToRad(cubed->player.pa));
	cubed->player.dy = -sin(degToRad(cubed->player.pa));
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
	load_text(cubed);
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
