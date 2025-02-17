/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:04:14 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/16 16:34:06 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "so_long.h"

int	handle_destroy(t_game *game)
{
	cleanup_game(game);
	free_tab(game->map);
	ft_printf("You exit the game whit the x\n");
	exit(0);
	return (0);
}

void	cleanup_images(t_game *game)
{
	if (game->mlx.wall && game->mlx.mlx_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.wall);
	if (game->mlx.floor && game->mlx.mlx_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.floor);
	if (game->mlx.player && game->mlx.mlx_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.player);
	if (game->mlx.exit && game->mlx.mlx_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.exit);
	if (game->mlx.collect1 && game->mlx.mlx_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.collect1);
	if (game->mlx.collect2 && game->mlx.mlx_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.collect2);
	if (game->mlx.collect3 && game->mlx.mlx_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.collect3);
}

int	cleanup_game(t_game *game)
{
	cleanup_images(game);
	if (game->mlx.win_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	if (game->mlx.mlx_ptr)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
	}
	return (0);
}
