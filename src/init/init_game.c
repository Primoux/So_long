/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:00:32 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/12 18:55:43 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <fcntl.h>
#include <unistd.h>

static int	check_map_errors(t_game *game, size_t i)
{
	if (i < 3 || game->line == NULL || game->line[ft_strlen(game->line)
		- 1] == '\n' || ft_strnstr(game->line, "\n\n", ft_strlen(game->line)))
		return (1);
	return (0);
}

static int	read_map(t_game *game, size_t *i)
{
	char	*line;

	line = get_next_line(game->fd);
	while (line != NULL)
	{
		game->line = str_free_to_join(game->line, line);
		if (!game->line)
		{
			free(line);
			return (1);
		}
		(*i)++;
		free(line);
		line = get_next_line(game->fd);
	}
	return (0);
}

char	**create_map(t_game *game)
{
	size_t	i;
	char	**map;

	i = 0;
	game->line = ft_strdup("");
	if (!game->line)
		return (NULL);
	if (game->fd < 0)
		return (NULL);
	if (read_map(game, &i) == 1)
		return (NULL);
	if (check_map_errors(game, i) == 1)
		return (NULL);
	map = ft_split(game->line, '\n');
	if (!map)
		return (NULL);
	game->count_line = i;
	game->line_len = ft_strlen(map[0]);
	free(game->line);
	return (map);
}

int	init_map(t_game *game)
{
	game->fd = open(game->map_path, O_RDONLY);
	if (game->fd < 0)
	{
		ft_putstr_fd("Error\nCannot open file\n", 2);
		return (1);
	}
	game->map = create_map(game);
	close(game->fd);
	if (!game->map)
	{
		free_tab(game->map);
		free(game->line);
		return (1);
	}
	if (parsing(game) == 1)
	{
		free_tab(game->map);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	game.map_path = argv[1];
	if (check_argv(game.map_path) == 1)
	{
		ft_putstr_fd("Error\nWrong arg\n", 2);
		return (1);
	}
	if (init_map(&game) == 1)
		return (1);
	if (check_map_valid(&game) == 1)
	{
		free_tab(game.map);
		return (1);
	}
	if (init_window(&game) != 0)
	{
		free_tab(game.map);
		return (1);
	}
	return (0);
}
