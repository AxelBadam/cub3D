#include "cub3d.h"

int mapX = 8;
int mapY = 8;
int	mapS = 64;
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

void	my_pixel_put(mlx_image_t *image, int x, int y, int color)
{
	if (y < HEIGHT && y > 0 && x < WIDTH && x > 0)
		mlx_put_pixel(image, x, y, color);
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
float dist(float ax, float ay, float bx, float by, float ang)
{
	(void)ang;
	return(sqrt((bx-ay) * (bx-ax) + (by - ay) * (by - ay)));
}

void	draw_horizontal(t_cubed *cubed)
{
	int r, mx, my, mp, dof; float rx, ry, ra, xo, yo;
	ra = cubed->player.pa;
	for (r = 0; r < 1; r++)
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
		if (ra < PI)
		{
			ry = (((int)cubed->player.py >> 6) << 6) + 64;
			rx = (cubed->player.py - ry) * aTan + cubed->player.px;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)
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
					disH = dist(cubed->player.px, cubed->player.py, hx, hy, ra);
					dof = 8;
				}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		plotline(cubed, (t_vec){cubed->player.px + 2, cubed->player.py + 2, 0, 0xFF00FFFF}, (t_vec){rx, ry, 0, 0xFF00FFFF});
	}
}
void	draw_vertical(t_cubed *cubed)
{
	int r, mx, my, mp, dof; float rx, ry, ra, xo, yo;
	ra = cubed->player.pa;
	for (r = 0; r < 1; r++)
	{
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
		if (ra ==0 || ra == PI)
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
				disV = dist(cubed->player.px, cubed->player.py, vx, vy, ra);
				dof = 8;
			}
				
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		plotline(cubed, (t_vec){cubed->player.px + 2, cubed->player.py + 2, 0, 0xFF0000FF}, (t_vec){rx, ry, 0, 0xFF0000FF});
	}	
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

	draw_horizontal(cubed);
	draw_vertical(cubed);
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
		cubed->player.pa += 2 * PI;
	else if (cubed->player.pa > (2 * PI))
		cubed->player.pa -= 2 * PI;
	cubed->player.dx = cos(cubed->player.pa) * 5;
	cubed->player.dy = sin(cubed->player.pa) * 5;
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
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_REPEAT || keydata.action == MLX_RELEASE))
		exit(0);
	draw(cubed);
}
