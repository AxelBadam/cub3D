/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:05:22 by ekoljone          #+#    #+#             */
/*   Updated: 2023/07/31 16:39:53 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define WIDTH 1024
#define HEIGHT 512

void	error_handling(char *str)
{
	ft_printf("%s", str);
}
/*
void	load_png(t_cubed *cubed, int i, char *path)
{
	mlx_texture_t	*txt;

	txt = mlx_load_png(path);
	cubed->mlx[i] = mlx_texture_to_image(cubed->mlx, txt);
	mlx_delete_texture(txt);
}*/

void	drawplayer(void *param)
{
	t_cubed *cubed = param;
	int start_x;
	int start_y;
	int x_pixels = 10;
	int y_pixels = 10;
	
	start_x = cubed->player->x;
	start_y = cubed->player->y;
	mlx_delete_image(cubed->mlx, cubed->mlx);
	cubed->mlx = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	while (y_pixels > 0)
	{
		while (x_pixels > 0)
		{
			mlx_put_pixel(cubed->mlx, cubed->player->x, cubed->player->y, cubed->player->color);
			cubed->player->x++;
			x_pixels--;
		}
		cubed->player->x = start_x;
		cubed->player->y++;
		y_pixels--;
		x_pixels = 10;
	}
	cubed->player->x = start_x;
	cubed->player->y = start_y;
	mlx_image_to_window(cubed->mlx, cubed->mlx, 0, 0);
}


void	init(t_cubed *cubed)
{
	cubed->player = malloc(sizeof(t_player));
	cubed->map = malloc(sizeof(t_map));
	cubed->map->x = 8;
	cubed->map->y = 8;
	cubed->map->color = 0;
	cubed->map->size = 64;
	int map_array[] = { 1,1,1,1,1,1,1,1,
						1,0,0,0,0,0,0,1,
						1,0,0,0,0,0,0,1,
						1,1,1,0,0,0,0,1,
						1,0,0,0,0,0,0,1,
						1,0,0,0,1,0,0,1,
						1,0,0,0,1,0,0,1,
						1,0,0,0,1,0,0,1,
						1,1,1,1,1,1,1,1 };
	cubed->map->map = map_array;
	cubed->player->x = 290;
	cubed->player->y = 290;
	cubed->changes = 0;
	cubed->player->color = 0xFF00FF;
	cubed->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
}

void keyhook(mlx_key_data_t keydata, void *param)
{	
	t_cubed *cubed;
	
	cubed = (t_cubed *)param;

	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		{
			cubed->player->x -= 5;
			cubed->changes = 1;
		}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		{
			cubed->player->x += 5;
			cubed->changes = 1;
		}
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		{
			cubed->player->y -= 5;
			cubed->changes = 1;
		}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		{
			cubed->player->y += 5;
			cubed->changes = 1;
		}
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_RELEASE)
		cubed->player->color += 4000;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		exit (0);
}

void draw_line(int begin_x, int begin_y, int end_x, int end_y, int color, t_cubed *cubed)
{
	double deltaX = end_x - begin_x; // 10
	double deltaY = end_y - begin_y; // 0
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	double pixelX = begin_x;
	double pixelY = begin_y;
	
	while (pixels)
	{
    	mlx_put_pixel(cubed->mlx, pixelX, pixelY, color);
   		pixelX += deltaX;
  	 	pixelY += deltaY;
   		--pixels;
	}	
}

void draw_map2d(t_cubed *cubed)
{
	int x,y,xo,yo = 0;
	
	while (y < cubed->map->y)
	{
		while (x < cubed->map->x)
		{
			if (cubed->map->map[y * cubed->map->x + x == 1])
			{
				draw_line()
			}
		}
		y++;
	}
}

void update_change(void *param)
{
	t_cubed *cubed;
	
	cubed = (t_cubed *)param;
	
	if (cubed->changes == 1)
	{
		drawplayer(cubed);
	}
	cubed->changes = 0;
}

int	main(void)
{
	t_cubed	*cubed;
	
	cubed = malloc(sizeof(t_cubed));
	//mlx_set_setting(MLX_MAXIMIZED, true);
	//mlx_loop_hook(cubed->mlx, ft_hook, cubed->mlx);
	//mlx_cursor_hook(cubed->mlx, mouse, NULL);
	//load_png(cubed, 0, "./image.png");
	//load_png(cubed, 1, "./playbutton.png");
	//mlx_image_to_window(cubed->mlx, cubed->mlx[0], 0, 0);
	init(cubed);
	draw_map2d(cubed);
	drawplayer(cubed);
	mlx_key_hook(cubed->mlx, &keyhook, cubed);
	mlx_loop_hook(cubed->mlx, &update_change, cubed);
	mlx_loop(cubed->mlx);
	return (0);
}