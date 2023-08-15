/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:05:22 by ekoljone          #+#    #+#             */
/*   Updated: 2023/08/15 18:51:40 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define WIDTH 1024
#define HEIGHT 512
#define PI 3.1415926535

void drawrays(t_cbd *cbd);

void	error_handling(char *str)
{
	ft_printf("%s", str);
}

void draw_line(int begin_x, int begin_y, int end_x, int end_y, int color, mlx_image_t *img)
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
    	mlx_put_pixel(img, pixelX, pixelY, color);
   		pixelX += deltaX;
  	 	pixelY += deltaY;
   		--pixels;
	}
}

void	drawplayer(void *param)
{
	t_cbd *cbd = param;
	
	int start_x;
	int start_y;
	int x_pixels = 10;
	int y_pixels = 10;

	start_x = cbd->player->x;
	start_y = cbd->player->y;
	mlx_delete_image(cbd->mlx, cbd->img);
	cbd->img = mlx_new_image(cbd->mlx, WIDTH, HEIGHT);
	while (y_pixels > 0)
	{
		while (x_pixels > 0)
		{
			mlx_put_pixel(cbd->img, cbd->player->x, cbd->player->y, cbd->player->color);
			cbd->player->x++;
			x_pixels--;
		}
		cbd->player->x = start_x;
		cbd->player->y++;
		y_pixels--;
		x_pixels = 10;
	}
	cbd->player->x = start_x;
	cbd->player->y = start_y;
	draw_line(cbd->player->x + 5, cbd->player->y + 5, cbd->player->x + cbd->player->pdx * 5, cbd->player->y + cbd->player->pdy * 5, 0xFFFF00FF, cbd->img);
	mlx_image_to_window(cbd->mlx, cbd->img, 0, 0);
}

void keyhook(mlx_key_data_t keydata, void *param)
{	
	t_cbd *cbd;
	
	cbd = (t_cbd *)param;

	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		{
			cbd->player->pa -= 0.1;
			if (cbd->player->pa < 0)
				cbd->player->pa += 2 * PI;
			cbd->player->pdx = cos(cbd->player->pa) * 5;
			cbd->player->pdy = sin(cbd->player->pa) * 5;
			cbd->changes = 1;
		}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		{
			cbd->player->pa += 0.1;
			if (cbd->player->pa > 2 * PI)
				cbd->player->pa -= 2 * PI;
			cbd->player->pdx = cos(cbd->player->pa) * 5;
			cbd->player->pdy = sin(cbd->player->pa) * 5;
			cbd->changes = 1;
		}
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		{
			cbd->player->x += cbd->player->pdx;
			cbd->player->y += cbd->player->pdy;
			cbd->changes = 1;
		}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT ||keydata.action == MLX_RELEASE))
		{
			cbd->player->x -= cbd->player->pdx;
			cbd->player->y -= cbd->player->pdy;
			cbd->changes = 1;
		}
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_RELEASE)
		cbd->player->color += 4000;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		exit (0);
}

int render_rect(t_cbd *cbd, t_rect rect)
{
    int	i;
    int j;

  	if (cbd->mlx == NULL)
        return (1);
    i = rect.y;
    while (i < rect.y + rect.height)
    {
        j = rect.x;
        while (j < rect.x + rect.width)
            mlx_put_pixel(cbd->map_img, j++, i, rect.color);
        ++i;
    }
	mlx_image_to_window(cbd->mlx, cbd->map_img, 0 , 0);
    return (0);
}

void update_change(void *param)
{
	t_cbd *cbd;
	
	cbd = (t_cbd *)param;
	
	if (cbd->changes == 1)
	{
		drawplayer(cbd);
		drawrays(cbd);
	}
	cbd->changes = 0;
}

t_cbd	*init(t_cbd *cbd)
{
	cbd = malloc(sizeof(t_cbd));
	cbd->player = malloc(sizeof(t_player));
	cbd->rect =  malloc(sizeof(t_rect));
	cbd->map = malloc(sizeof(t_map));
	cbd->ray = malloc(sizeof(t_ray));
	cbd->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	cbd->img = mlx_new_image(cbd->mlx, WIDTH, HEIGHT);
	cbd->map_img = mlx_new_image(cbd->mlx, WIDTH, HEIGHT);
	cbd->ray_img = mlx_new_image(cbd->mlx, WIDTH, HEIGHT);
	cbd->rect->height = 100;
	cbd->rect->width = 100;
	cbd->map->x = 8;
	cbd->map->y = 8;
	cbd->map->map_x = 8;
	cbd->map->map_y = 8;
	cbd->map->color = 0xFFFFFF;
	cbd->map->size = 64;
	cbd->rect->x = 8;
	cbd->rect->y = 8;
	cbd->rect->height = 64;
	cbd->rect->width = 64;
	cbd->player->x = 290;
	cbd->player->y = 290;
	cbd->player->pdx = 0;
	cbd->player->pdy = 0;
	cbd->player->pa = 0;
	cbd->changes = 0;
	cbd->player->color = 0xFF00FFFF;
	return (cbd);
}

void draw_map(t_cbd *cbd)
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
	cbd->map->map = map;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (map[i] && map[i] == 1)
				color = 0xFFFFFFFF;
			else
				color = 0x000000FF;
			render_rect(cbd, (t_rect){x, y, WIDTH / 8 - 1, HEIGHT / 8 - 1, color});
			x += WIDTH / 8;
			i++;
		}
		x = 1;
		y += HEIGHT / 8;
	}
}

void drawrays(t_cbd *cbd)
{
	t_ray *ray;
	float a_tan;

	ray = cbd->ray;
	ray->ra = cbd->player->pa;

	while (ray->r < 1)
	{
		ray->r = 0;
		ray->dof = 0;
		a_tan = -1/tan(ray->ra);
		if (ray->ra > PI)
		{
			ray->ry = (((int)cbd->player->y >> 6) << 6) - 0.0001;
			ray->rx = (cbd->player->y - ray->ry) * a_tan + cbd->player->x;
			ray->yo = -64;
			ray->xo = -ray->yo * a_tan;
		}
		if (ray->ra < PI)
		{
			ray->ry = (((int)cbd->player->y >> 6) << 6) + 64;
			ray->rx = (cbd->player->y - ray->ry) * a_tan + cbd->player->x;
			ray->yo = 64;
			ray->xo = -ray->yo * a_tan;
		}
		if (ray->ra == 0 || ray->ra == PI)
		{
			ray->rx = cbd->player->x;
			ray->ry = cbd->player->y;
			ray->dof = 8;
		}
		while (ray->dof < 8)
		{
			ray->mx = (int) (ray->rx) >> 6;
			ray->my = (int) (ray->ry) >> 6;	
			ray->mp = ray->my * cbd->map->map_x + ray->mx;
			if (ray->mp < cbd->map->map_x * cbd->map->map_y && cbd->map->map[ray->mp] == 1)
				ray->dof = 8;
			else
			{
				ray->rx += ray->xo;
				ray->ry += ray->yo;
				ray->dof += 1;
			}
		}
	mlx_delete_image(cbd->mlx, cbd->ray_img);
	cbd->ray_img = mlx_new_image(cbd->mlx, WIDTH, HEIGHT);
	draw_line(cbd->player->x + 5, cbd->player->y + 5, ray->rx, ray->ry, 0xFF00FFFF, cbd->ray_img);
	mlx_image_to_window(cbd->mlx, cbd->ray_img, 0, 0);
	ray->r += 1;
	}
}

void	draw_background(t_cbd *cbd, mlx_image_t *img)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	(void)cbd;
	
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(img, x, y, 0xFF0000FF);
			else
				mlx_put_pixel(img, x, y, 0xFF00FFFF);
			x++;
		}
		x = 0;
		y++;
	}
}

int	main(void)
{
	t_cbd	*cbd;

	cbd = NULL;
	cbd = init(cbd);
	draw_map(cbd);
	drawplayer(cbd);
	drawrays(cbd);
	//draw_background(cbd, cbd->img);
	mlx_image_to_window(cbd->mlx, cbd->img, 0, 0);
	mlx_key_hook(cbd->mlx, &keyhook, cbd);
	mlx_loop_hook(cbd->mlx, &update_change, cbd);
	mlx_loop(cbd->mlx);
	return (0);
}

//load_png(cbd, 0, "./image.png");
//load_png(cbd, 1, "./playbutton.png");
//mlx_cursor_hook(cbd7.7444->mlx, mouse, NULL);
/*
void draw_map2d(t_cbd *cbd)
{
	int x;
	int y;
	int xo;
	int yo;

	x = 0;
	y = 0;
	xo = 0;
	yo = 0;
	
	for (y= 0; y < cbd->map->y; y++)
	{
		for (x = 0; x < cbd->map->x; x++)
		{
			if (cbd->map->map[y * cbd->map->x + x == 1])
				cbd->map->color = 0xFFFFFF;
			else
				cbd->map->color = 0xFFFFFF;
			draw_line(x, y, xo, yo, cbd->map->color, cbd);
		}
	}
}*/

/*
void	load_png(t_cbd *cbd, int i, char *path)
{
	mlx_texture_t	*txt;

	txt = mlx_load_png(path);
	cbd->mlx[i] = mlx_texture_to_image(cbd->mlx, txt);
	mlx_delete_texture(txt);
}*/
