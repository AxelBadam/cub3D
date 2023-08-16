/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:05:22 by ekoljone          #+#    #+#             */
/*   Updated: 2023/08/16 16:10:08 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int mapX = 8;
int mapY = 8;
int	mapS = 64;
int	map[] =
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,1,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

void	my_pixel_put(mlx_image_t *image, int x, int y, int color)
{
	if (y < HEIGHT && y > 0 && x < WIDTH && x > 0)
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

/*float dist(float ax, float ay, float bx, float by, float ang)
{
	(void)ang;
	return(sqrt((bx-ay) * (bx-ax) + (by - ay) * (by - ay)));
}*/

float degToRad(int a) { return a*M_PI/180.0;}
int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}
float distance(ax,ay,bx,by,ang){ return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);}


void drawRays2D(t_cubed *cubed)
{
 int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
 
 ra=FixAng(cubed->player.pa+30);                                                              //ray set back 30 degrees
 
 for(r=0;r<60;r++)
 {
  //---Vertical--- 
  dof=0; side=0; disV=100000;
  float Tan=tan(degToRad(ra));
       if(cos(degToRad(ra))> 0.001){ rx=(((int)cubed->player.px>>6)<<6)+64;      ry=(cubed->player.px-rx)*Tan+cubed->player.py; xo= 64; yo=-xo*Tan;}//looking left
  else if(cos(degToRad(ra))<-0.001){ rx=(((int)cubed->player.px>>6)<<6) -0.0001; ry=(cubed->player.px-rx)*Tan+cubed->player.py; xo=-64; yo=-xo*Tan;}//looking right
  else { rx=cubed->player.px; ry=cubed->player.py; dof=8;}                                                  //looking up or down. no hit  

  while(dof<8) 
  { 
   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
   if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-cubed->player.px)-sin(degToRad(ra))*(ry-cubed->player.py);}//hit         
   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  } 
  vx=rx; vy=ry;

  //---Horizontal---
  dof=0; disH=100000;
  Tan=1.0/Tan; 
       if(sin(degToRad(ra))> 0.001){ ry=(((int)cubed->player.py>>6)<<6) -0.0001; rx=(cubed->player.py-ry)*Tan+cubed->player.px; yo=-64; xo=-yo*Tan;}//looking up 
  else if(sin(degToRad(ra))<-0.001){ ry=(((int)cubed->player.py>>6)<<6)+64;      rx=(cubed->player.py-ry)*Tan+cubed->player.px; yo= 64; xo=-yo*Tan;}//looking down
  else{ rx=cubed->player.px; ry=cubed->player.py; dof=8;}                                                   //looking straight left or right
 
  while(dof<8) 
  { 
   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
   if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disH=cos(degToRad(ra))*(rx-cubed->player.px)-sin(degToRad(ra))*(ry-cubed->player.py);}//hit         
   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  } 
  
  if(disV<disH){ rx=vx; ry=vy; disH=disV;}                  //horizontal hit first
  plotline(cubed, (t_vec){cubed->player.px + 2, cubed->player.py + 2, 0, 0xFF0000FF}, (t_vec){rx, ry, 0, 0xFF0000FF});
  int ca=FixAng(cubed->player.pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
  int lineH = (mapS*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
  int lineOff = 160 - (lineH>>1);                                               //line offset
  plotline(cubed, (t_vec){r*8+530, lineOff, 0, 0xFF0000FF}, (t_vec){r*8+530, lineOff+lineH, 0, 0xFF0000FF});
  ra=FixAng(ra-1);                                                              //go to next ray
 }
}

/*void	draw_rays(t_cubed *cubed)
{
	int r, mx, my, mp, dof; float rx, ry, ra, xo, yo;
	ra = cubed->player.pa - DR * 30;
	if (ra < 0)
		ra += 2 * (float)M_PI;
	if (ra > 2 * (float)M_PI)
		ra -= 2* (float)M_PI;
	for (r = 0; r < 60; r++)
	{
		dof = 0;
		float disH = 1000000, hx = cubed->player.px, hy = cubed->player.py;
		float aTan = -1 / tan(ra);
		if (ra > PI)
		{
			ry = (((int)cubed->player.py >> 6) << 6) -0.0001;
			rx = (cubed->player.py - ry) * aTan + cubed->player.px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < (float)M_PI)
		{
			ry = (((int)cubed->player.py >> 6) << 6) + 64;
			rx = (cubed->player.py - ry) * aTan + cubed->player.px;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == (float)M_PI)
		{
			rx = cubed->player.px;
			ry = cubed->player.py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
			{
				hx = rx;
				hy = ry;
				disH = (float)dist(cubed->player.px, cubed->player.py, hx, hy, ra);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		// check vertical
		dof = 0;
		float disV = 1000000, vx = cubed->player.px, vy = cubed->player.py;
		float nTan = -tan(ra);
		if (ra > P2 && ra < P3)
		{
			rx = (((int)cubed->player.px >> 6) << 6) -0.0001;
			ry = (cubed->player.px - rx) * nTan + cubed->player.py;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3)
		{
			rx = (((int)cubed->player.px >> 6) << 6) + 64;
			ry = (cubed->player.px - rx) * nTan + cubed->player.py;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra ==0 || ra == (float)M_PI)
		{
			rx = cubed->player.px;
			ry = cubed->player.py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
			{
				vx = rx;
				vy = ry;
				disV = (float)dist(cubed->player.px, cubed->player.py, vx, vy, ra);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
		}
		if (disH < disV)
		{
			rx = hx;
			ry = hy;
		}
		printf("DISV == %f -- DISH %f\n", disV, disH);
		plotline(cubed, (t_vec){cubed->player.px + 2, cubed->player.py + 2, 0, 0xFF0000FF}, (t_vec){rx, ry, 0, 0xFF0000FF});
		ra += DR;
		if (ra < 0)
			ra += 2 * (float)M_PI;
		if (ra > 2 * (float)M_PI)
			ra -= 2 * (float)M_PI;
	}	
}*/

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
			my_pixel_put(cubed->mlx.image, x, y, 0xFF00FFFF);
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
	if (key == 'D')
		cubed->player.pa -= 5;
	else
		cubed->player.pa += 5;
	cubed->player.pa=FixAng(cubed->player.pa);
	cubed->player.dx=cos(degToRad(cubed->player.pa));
	cubed->player.dy=-sin(degToRad(cubed->player.pa));
}

void	move_player(t_cubed *cubed, int key)
{
	if (key == 'W')
	{
		cubed->player.px += cubed->player.dx * 5;
		cubed->player.py += cubed->player.dy * 5;
	}
	else
	{
		cubed->player.px -= cubed->player.dx * 5;
		cubed->player.py -= cubed->player.dy * 5;
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

void	draw_rectangle(t_cubed *cubed, int ry, int rx, int color)
{
	int	x = 0;
	int y = ry;

	while (y < ry + mapS - 1)
	{
		x = rx;
		while (x < rx + mapS - 1)
			my_pixel_put(cubed->mlx.image, x++, y, color);
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
	
	while (y < mapY)
	{
		while (x < mapX)
		{
			if (map[y * mapX + x] == 1)
				color = 0xFFFFFFFF;
			else
				color = 0x000000FF;
			xo = x * mapS;
			yo = y * mapS;
			draw_rectangle(cubed, yo, xo, color);
			x++;
			i++;
		}
		x = 0;
		y++;
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
