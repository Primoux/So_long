/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:05:56 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/23 15:48:48 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "so_long.h"
#include <X11/keysym.h>
#include <stdlib.h>

static int	load_images(t_mlx_data *mlx, t_game *game)
{
	int	w;
	int	h;

	mlx->wall = mlx_xpm_file_to_image(mlx->mlx_ptr, "./xpm/Wall.xpm", &w, &h);
	mlx->floor = mlx_xpm_file_to_image(mlx->mlx_ptr, "./xpm/grass.xpm", &w, &h);
	mlx->player = mlx_xpm_file_to_image(mlx->mlx_ptr, "./xpm/Player.xpm", &w,
			&h);
	mlx->exit = mlx_xpm_file_to_image(mlx->mlx_ptr, "./xpm/Door_close.xpm", &w,
			&h);
	game->mlx.collect1 = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->mlx.collect1, &w, &h);
	game->mlx.collect2 = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->mlx.collect2, &w, &h);
	game->mlx.collect3 = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->mlx.collect3, &w, &h);
	if (!mlx->wall || !mlx->floor || !mlx->player || !mlx->exit
		|| !mlx->collect1 || !mlx->collect2 || !mlx->collect3)
		return (1);
	return (0);
}

int	init_mlx_resources(t_game *game, t_mlx_data *mlx)
{
	int	map_width;
	int	map_height;

	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (1);
	map_width = game->line_len * mlx->pixel_size;
	map_height = game->count_line * mlx->pixel_size;
	mlx->offset_x = (WIDTH - map_width) / 2;
	mlx->offset_y = (HEIGHT - map_height - 150) / 2;
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, map_width + (mlx->offset_x * 2),
			map_height + (mlx->offset_y * 2), "So_Long");
	if (!mlx->win_ptr)
	{
		ft_putstr_fd("Error\nWindow ptr failed\n", 2);
		return (1);
	}
	if (load_images(mlx, game))
	{
		ft_putstr_fd("Error\nMissing or moved XPM files\n", 2);
		return (1);
	}
	return (0);
}

void	put_sprite(t_mlx_data *data, char c, size_t x, size_t y)
{
	void	*sprite;
	void	*collectibles[3];

	collectibles[0] = data->collect1;
	collectibles[1] = data->collect2;
	collectibles[2] = data->collect3;
	if (c == '1')
		sprite = data->wall;
	else if (c == '0')
		sprite = data->floor;
	else if (c == 'P')
		sprite = data->player;
	else if (c == 'E')
		sprite = data->exit;
	else if (c == 'C')
		sprite = collectibles[(x + y) % 3];
	else
		return ;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, sprite, data->offset_x
		+ (x * data->pixel_size), data->offset_y + (y * data->pixel_size));
}

void	render_game(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < game->count_line)
	{
		x = 0;
		while (x < game->line_len)
		{
			put_sprite(&game->mlx, game->map[y][x], x, y);
			x++;
		}
		y++;
	}
}
