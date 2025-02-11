/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:10:38 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/08 19:23:00 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

int	check_walls_up_down(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->line_len)
	{
		if (game->map[0][i] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (game->map[game->count_line - 1][i])
	{
		if (game->map[game->count_line - 1][i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_walls_left_right(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->count_line)
	{
		if (game->map[i][0] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (i < game->count_line)
	{
		if (game->map[i][game->line_len - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_line_len(t_game game)
{
	size_t	i;

	i = 0;
	while (game.map[i])
	{
		if (ft_strlen(game.map[i]) != game.line_len)
		{
			return (1);
		}
		i++;
	}
	return (0);
}
