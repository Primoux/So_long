/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:17:51 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/17 19:11:44 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "so_long.h"
#include <X11/keysym.h>
#include <unistd.h>

static int	process_movement(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
	{
		cleanup_game(game);
		free_tab(game->map);
		exit(0);
	}
	else if (keysym == XK_w || keysym == XK_Up)
		game->player_y--;
	else if (keysym == XK_s || keysym == XK_Down)
		game->player_y++;
	else if (keysym == XK_a || keysym == XK_Left)
		game->player_x--;
	else if (keysym == XK_d || keysym == XK_Right)
		game->player_x++;
	else
		return (0);
	return (1);
}

int	handle_input(int keysym, t_game *game)
{
	int	old_x;
	int	old_y;

	old_x = game->player_x;
	old_y = game->player_y;
	if (!process_movement(keysym, game))
		return (0);
	if (check_collision(game, old_x, old_y) == 1)
		return (0);
	update_player_pos(game, old_x, old_y);
	return (0);
}

static int	handle_exit_update(t_game *game)
{
	int	w;
	int	h;

	mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.exit);
	game->mlx.exit = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			"./xpm/Door_open.xpm", &w, &h);
	if (!game->mlx.exit)
	{
		put_on_screen(game);
		cleanup_game(game);
		free_tab(game->map);
		ft_putstr_fd("Error\nDon't move the xpm files pls\n", 2);
		exit(1);
	}
	return (0);
}

int	check_collision(t_game *game, size_t old_x, size_t old_y)
{
	if (game->map[game->player_y][game->player_x] == '1')
	{
		game->player_x = old_x;
		game->player_y = old_y;
		return (1);
	}
	game->on_exit = (game->player_x == game->exit_x
			&& game->player_y == game->exit_y);
	if (game->map[game->player_y][game->player_x] == 'C')
		game->char_count.c_count--;
	if (game->char_count.c_count == 0)
		if (handle_exit_update(game))
			return (1);
	if (game->on_exit && game->char_count.c_count == 0)
	{
		cleanup_game(game);
		free_tab(game->map);
		ft_printf("You Finished the game in %d moves GG !\n", game->move_count);
		exit(0);
	}
	return (0);
}

void	update_player_pos(t_game *game, size_t old_x, size_t old_y)
{
	if (game->map[old_y][old_x] == 'P')
	{
		if (old_x == game->exit_x && old_y == game->exit_y)
			game->map[old_y][old_x] = 'E';
		else
			game->map[old_y][old_x] = '0';
	}
	game->map[game->player_y][game->player_x] = 'P';
	put_sprite(&game->mlx, 'P', game->player_x * game->mlx.pixel_size,
		game->player_y * game->mlx.pixel_size);
	render_game(*game);
	put_on_screen(game);
}
