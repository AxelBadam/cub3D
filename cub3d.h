/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:18:08 by ekoljone          #+#    #+#             */
/*   Updated: 2023/08/29 13:50:15 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
#include <stdio.h>

char	**append_2d(char **twod, char *str_to_add);
void	free_string_array(char **array);
int		get_2d_array_size(char **array);
void	draw_map(t_cubed *cubed);
char	**append_2d(char **twod, char *str_to_add);
void	free_string_array(char **array);
int		get_2d_array_size(char **array);
void	draw_map(t_cubed *cubed);