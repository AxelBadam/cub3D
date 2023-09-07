/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:21:14 by ekoljone          #+#    #+#             */
/*   Updated: 2023/09/07 16:27:29 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	free_all(t_cubed *cubed)
{
	if (cubed->mlx.image)
		mlx_delete_image(cubed->mlx.mlx, cubed->mlx.image);
	if (cubed->mlx.mlx)
		mlx_terminate(cubed->mlx.mlx);
	if (cubed->north)
		mlx_delete_texture(cubed->north);
	if (cubed->south)
		mlx_delete_texture(cubed->south);
	if (cubed->east)
		mlx_delete_texture(cubed->east);
	if (cubed->west)
		mlx_delete_texture(cubed->west);
	if (cubed->map.path_to_east)
		free(cubed->map.path_to_east);
	if (cubed->map.path_to_west)
		free(cubed->map.path_to_west);
	if (cubed->map.path_to_south)
		free(cubed->map.path_to_south);
	if (cubed->map.path_to_north)
		free(cubed->map.path_to_north);
	if (cubed->map.map)
		free(cubed->map.map);
}

void	error_exit(t_cubed *cubed, char *error_msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_msg, 2);
	if (cubed)
		free_all(cubed);
	exit(1);
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
