/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:05:22 by ekoljone          #+#    #+#             */
/*   Updated: 2023/08/03 16:56:54 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define WIDTH 1024
#define HEIGHT 512
#define PI 3.1415926535

void	error_handling(char *str)
{
	ft_printf("%s", str);
}

void	drawplayer(void *param)
{
	t_cubed *cubed = param;
	int start_x;
	int start_y;
	int x_pixels = 10;
	int y_pixels = 10;
	
	start_x = cubed->player->x;
	start_y = cubed->player->y;
	mlx_delete_image(cubed->mlx, cubed->img);
	cubed->img = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	while (y_pixels > 0)
	{
		while (x_pixels > 0)
		{
			mlx_put_pixel(cubed->img, cubed->player->x, cubed->player->y, cubed->player->color);
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
	mlx_image_to_window(cubed->mlx, cubed->img, 0, 0);
}

void keyhook(mlx_key_data_t keydata, void *param)
{	
	t_cubed *cubed;
	
	cubed = (t_cubed *)param;

	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		{
			cubed->player->x -= 10;
			cubed->changes = 1;
		}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		{
			cubed->player->x += 10;
			cubed->changes = 1;
		}
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		{
			cubed->player->y -= 10;
			cubed->changes = 1;
		}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT ||keydata.action == MLX_RELEASE))
		{
			cubed->player->y += 10;
			cubed->changes = 1;
		}
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_RELEASE)
		cubed->player->color += 4000;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		exit (0);
}

void draw_line(int begin_x, int begin_y, int end_x, int end_y, int color, t_cubed *cubed)
{
	double deltaX = end_x - begin_x;
	double deltaY = end_y - begin_y;
	double pixelX = begin_x;
	double pixelY = begin_y;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	
	while (pixels)
	{
    	mlx_put_pixel(cubed->map_img, pixelX, pixelY, color);
   		pixelX += deltaX;
  	 	pixelY += deltaY;
   		--pixels;
	}
	mlx_image_to_window(cubed->mlx, cubed->map_img, 0, 0);
}

int render_rect(t_cubed *cubed, t_rect rect)
{
    int	i;
    int j;

  	if (cubed->mlx == NULL)
        return (1);
    i = rect.y;
    while (i < rect.y + rect.height)
    {
        j = rect.x;
        while (j < rect.x + rect.width)
            mlx_put_pixel(cubed->map_img, j++, i, rect.color);
        ++i;
    }
	mlx_image_to_window(cubed->mlx, cubed->map_img, 0 , 0);
    return (0);
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

t_cubed	*init(t_cubed *cubed)
{
	cubed = malloc(sizeof(t_cubed));
	cubed->player = malloc(sizeof(t_player));
	cubed->rect =  malloc(sizeof(t_rect));
	cubed->map = malloc(sizeof(t_map));
	cubed->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	cubed->img = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	cubed->map_img = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	cubed->rect->height = 100;
	cubed->rect->width = 100;
	cubed->map->x = 8;
	cubed->map->y = 8;
	cubed->map->color = 0xFFFFFF;
	cubed->map->size = 64;
	cubed->rect->x = 8;
	cubed->rect->y = 8;
	cubed->rect->height = 64;
	cubed->rect->width = 64;
	cubed->player->x = 290;
	cubed->player->y = 290;
	cubed->changes = 0;
	cubed->player->color = 0xFF00FFFF;
	return (cubed);
}

void draw_map(t_cubed *cubed)
{
	int x = 1;
	int y = 1;
	int color = 0;
	int i = 0;
	int map[64] = {1,1,1,1,1,1,1,1,
				1,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,1,
				1,1,1,0,0,0,0,1,
				1,0,0,0,0,0,0,1,
				1,0,0,0,1,0,0,1,
				1,0,0,0,1,0,0,1,
				1,1,1,1,1,1,1,1,};
	
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (map[i] && map[i] == 1)
				color = 0xFFFFFFFF;
			else
				color = 0x000000FF;
			render_rect(cubed, (t_rect){x, y, WIDTH / 8 - 1, HEIGHT / 8 - 1, color});
			x += WIDTH / 8;
			i++;
		}
		x = 1;
		y += HEIGHT / 8;
	}
}

int	main(void)
{
	t_cubed	*cubed;

	cubed = NULL;
	cubed = init(cubed);
	draw_map(cubed);
	drawplayer(cubed);
	mlx_key_hook(cubed->mlx, &keyhook, cubed);
	mlx_loop_hook(cubed->mlx, &update_change, cubed);
	mlx_loop(cubed->mlx);
	return (0);
}

//load_png(cubed, 0, "./image.png");
//load_png(cubed, 1, "./playbutton.png");
//mlx_cursor_hook(cubed->mlx, mouse, NULL);
/*
void draw_map2d(t_cubed *cubed)
{
	int x;
	int y;
	int xo;
	int yo;

	x = 0;
	y = 0;
	xo = 0;
	yo = 0;
	
	for (y= 0; y < cubed->map->y; y++)
	{
		for (x = 0; x < cubed->map->x; x++)
		{
			if (cubed->map->map[y * cubed->map->x + x == 1])
				cubed->map->color = 0xFFFFFF;
			else
				cubed->map->color = 0xFFFFFF;
			draw_line(x, y, xo, yo, cubed->map->color, cubed);
		}
	}
}*/

/*
void	load_png(t_cubed *cubed, int i, char *path)
{
	mlx_texture_t	*txt;

	txt = mlx_load_png(path);
	cubed->mlx[i] = mlx_texture_to_image(cubed->mlx, txt);
	mlx_delete_texture(txt);
}*/