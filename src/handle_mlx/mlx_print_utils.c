/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_print_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:36:15 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/13 17:51:10 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <mlx.h>

int	put_on_screen(t_game *game)
{
	char	*count_str;

	game->move_count++;
	ft_printf("Move count : %d\n", game->move_count);
	count_str = ft_itoa(game->move_count);
	if (!count_str)
		return (1);
	mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, 10, 20, 0xFFFFFF,
		"Moves: ");
	mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, 60, 20, 0xFFFFFF,
		count_str);
	free(count_str);
	return (0);
}
