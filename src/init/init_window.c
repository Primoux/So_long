/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:35:41 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/23 15:51:05 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "so_long.h"
#include <X11/X.h>

int	init_window(t_game *game)
{
	game->mlx.collect1 = "./xpm/Pikmin_red.xpm";
	game->mlx.collect2 = "./xpm/Pikmin_blue.xpm";
	game->mlx.collect3 = "./xpm/Pikmin_yellow.xpm";
	game->move_count = 0;
	if (init_mlx_resources(game, &game->mlx) != 0)
	{
		cleanup_game(game);
		free_tab(game->map);
		exit(EXIT_FAILURE);
	}
	find_exit_pos(game);
	render_game(game);
	mlx_hook(game->mlx.win_ptr, 2, 1L << 0, handle_input, game);
	mlx_hook(game->mlx.win_ptr, DestroyNotify, StructureNotifyMask,
		handle_destroy, game);
	mlx_loop(game->mlx.mlx_ptr);
	return (0);
}
