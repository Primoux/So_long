/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_e_and_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:33:36 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/18 18:28:35 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* Header comment */

#include "libft.h"
#include "so_long.h"

void	find_player_pos(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < game->count_line)
	{
		x = 0;
		while (x < game->line_len)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	find_exit_pos(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < game->count_line)
	{
		x = 0;
		while (x < game->line_len)
		{
			if (game->map[y][x] == 'E')
			{
				game->exit_x = x;
				game->exit_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
