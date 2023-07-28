/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:05:22 by ekoljone          #+#    #+#             */
/*   Updated: 2023/07/28 17:55:58 by atuliara         ###   ########.fr       */
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
	cubed->img[i] = mlx_texture_to_image(cubed->mlx, txt);
	mlx_delete_texture(txt);
}*/

void	drawplayer(void *param)
{
	t_cubed *cubed = param;
	int start_x;
	int pixels = 10;
	
	start_x = cubed->player->x;
	mlx_delete_image(cubed->mlx, cubed->img);
	cubed->img = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	
	while (pixels > 0)
	{
		mlx_put_pixel(cubed->img, cubed->player->x, cubed->player->y, cubed->player->color);
		cubed->player->x++;
		pixels--;
	}
	cubed->player->y++;
	cubed->player->x = start_x;
	mlx_image_to_window(cubed->mlx, cubed->img, 0, 0);
}

void	init(t_cubed *cubed)
{
	cubed->player = malloc(sizeof(t_player));
	cubed->player->x = 290;
	cubed->player->y = 290;
	cubed->player->color = 0xFF00FF;
	cubed->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
}

void keyhook(mlx_key_data_t keydata, void *param)
{	
	t_cubed *cubed;
	
	cubed = (t_cubed *)param;

	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		{
				cubed->player->x -= 5;
		}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		{
			cubed->player->x += 5;
		}
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		{
			cubed->player->y -= 5;
		}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		{
			cubed->player->y += 5;
		}
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_RELEASE)
		cubed->player->color += 4000;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		exit (0);
	drawplayer(cubed);
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
	//mlx_image_to_window(cubed->mlx, cubed->img[0], 0, 0);
	init(cubed);
	//drawplayer((void *)cubed);
	mlx_key_hook(cubed->mlx, &keyhook, cubed);
	mlx_loop(cubed->mlx);
	return (0);
}