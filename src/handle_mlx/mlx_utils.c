/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:05:56 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/11 22:24:36 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include <X11/keysym.h>
#include <stdlib.h>

void	init_collectible(t_game *game, int w, int h)
{
	game->mlx.collect1 = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->mlx.collect1, &w, &h);
	game->mlx.collect2 = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->mlx.collect2, &w, &h);
	game->mlx.collect3 = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->mlx.collect3, &w, &h);
}

int	init_mlx_resources(t_game *game)
{
	int	w;
	int	h;

	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
		return (1);
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, game->line_len
			* game->mlx.pixel_size, game->count_line * game->mlx.pixel_size,
			"So Long");
	if (!game->mlx.win_ptr)
		return (cleanup_mlx(&game->mlx, NULL));
	game->mlx.wall = mlx_xpm_file_to_image(game->mlx.mlx_ptr, "./xpm/Wall.xpm",
			&w, &h);
	game->mlx.floor = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			"./xpm/grass.xpm", &w, &h);
	game->mlx.player = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			"./xpm/Player.xpm", &w, &h);
	game->mlx.exit = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			"./xpm/Door_close.xpm", &w, &h);
	init_collectible(game, w, h);
	if (!game->mlx.wall || !game->mlx.floor || !game->mlx.player
		|| !game->mlx.exit || !game->mlx.collect1 || !game->mlx.collect2
		|| !game->mlx.collect3)
		return (cleanup_mlx(&game->mlx, NULL));
	return (0);
}

void	put_sprite(t_mlx_data *data, char c, int x, int y)
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
