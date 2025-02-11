/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:04:14 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/11 22:28:52 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "so_long.h"

int	handle_destroy(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

int	cleanup_mlx(t_mlx_data *data, void *img)
{
	if (img)
		mlx_destroy_image(data->mlx_ptr, img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	return (1);
}

void	cleanup_images(t_game *game)
{
	if (game->mlx.wall)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.wall);
	if (game->mlx.floor)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.floor);
	if (game->mlx.player)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.player);
	if (game->mlx.exit)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.exit);
	if (game->mlx.collect1)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.collect1);
	if (game->mlx.collect2)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.collect2);
	if (game->mlx.collect3)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.collect3);
}

void	cleanup_game(t_game *game)
{
	cleanup_images(game);
	if (game->mlx.win_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	mlx_destroy_display(game->mlx.mlx_ptr);
	free(game->mlx.mlx_ptr);
}
