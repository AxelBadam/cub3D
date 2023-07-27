/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:05:22 by ekoljone          #+#    #+#             */
/*   Updated: 2023/07/27 18:17:43 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define WIDTH 1980
#define HEIGHT 1080

void	error_handling(char *str)
{
	ft_printf("%s", str);
}

void	create_bg(t_cube *game)
{
	mlx_texture_t	*txt;

	txt = mlx_load_png("./image.png");
	game->img = mlx_texture_to_image(game->mlx, txt);
	mlx_delete_texture(txt);
}

void	menu(t_cube *game)
{
	game->menu = malloc(sizeof(t_menu));
	if (game->menu == NULL)
		return (error_handling("error"));
	create_bg(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void ft_hook(void *param)
{
	const mlx_t* mlx = param;
	
	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

void keyhook(mlx_key_data_t keydata, void* param)
{
	(void)param;
	
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit (0); //free all?
		
}


void	mouse()
{
	
	return (0);
}

int	main(void)
{
	t_cube	*game;
	
	game = malloc(sizeof(t_cube));
	//mlx_set_setting(MLX_MAXIMIZED, true);
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	menu(game);
	//mlx_loop_hook(game->mlx, ft_hook, game->mlx);
	mlx_cursor_hook(game->mlx, mouse, NULL);
	mlx_key_hook(game->mlx, &keyhook, NULL);
	mlx_loop(game->mlx);
	return (0);
}