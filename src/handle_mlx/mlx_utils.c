/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:05:56 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/13 17:54:56 by enchevri         ###   ########lyon.fr   */
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
	int	win_wid;
	int	win_hei;

	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (1);
	mlx_get_screen_size(mlx->mlx_ptr, &mlx->screen_width, &mlx->screen_height);
	win_wid = game->line_len * mlx->pixel_size;
	win_hei = game->count_line * mlx->pixel_size;
	if (win_wid > mlx->screen_width || win_hei > mlx->screen_height)
	{
		ft_putstr_fd("Error\nMap too large for screen resolution\n", 2);
		return (1);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, win_wid, win_hei, "So_Long");
	if (!mlx->win_ptr)
		return (cleanup_game(game));
	if (load_images(mlx, game))
	{
		cleanup_game(game);
		ft_putstr_fd("Error\nCan't charge sprites\n", 2);
		free_tab(game->map);
		exit(1);
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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, sprite, x
		* data->pixel_size, y * data->pixel_size);
}

void	render_game(t_game game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < game.count_line)
	{
		x = 0;
		while (x < game.line_len)
		{
			put_sprite(&game.mlx, game.map[y][x], x, y);
			x++;
		}
		y++;
	}
}
