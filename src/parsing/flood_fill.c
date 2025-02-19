/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:46:13 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/19 19:01:55 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

char	**copy_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

int	check_map_valid(t_game *game)
{
	char	**map_copy;

	map_copy = copy_map(game->map, game->count_line);
	if (!map_copy)
		return (1);
	game->found_collectibles = 0;
	game->on_exit = FALSE;
	find_player_pos(game);
	flood_fill(map_copy, game->player_y, game->player_x, game);
	if (game->on_exit == FALSE
		|| game->found_collectibles != game->char_count.c_count)
	{
		ft_putendl_fd("Error\nImpossible map", 2);
		free_tab(map_copy);
		return (1);
	}
	free_tab(map_copy);
	return (0);
}

void	flood_fill(char **map, size_t y, size_t x, t_game *game)
{
	if (y >= game->count_line || x >= game->line_len)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'X')
		return ;
	if (map[y][x] == 'E')
	{
		game->on_exit = TRUE;
		return ;
	}
	if (map[y][x] == 'C')
		game->found_collectibles++;
	map[y][x] = 'X';
	flood_fill(map, y + 1, x, game);
	flood_fill(map, y - 1, x, game);
	flood_fill(map, y, x + 1, game);
	flood_fill(map, y, x - 1, game);
}
