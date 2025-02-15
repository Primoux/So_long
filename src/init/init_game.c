/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:00:32 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/15 17:27:49 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <fcntl.h>
#include <unistd.h>

static int	check_map_errors(t_game *game, size_t i)
{
	if (i < 3 || game->line == NULL || game->line[ft_strlen(game->line)
			- 1] == '\n' || ft_strnstr(game->line,
			"\n\n", ft_strlen(game->line)))
		return (1);
	return (0);
}

static int	read_map(t_game *game, size_t *count_line)
{
	char	*line;
	size_t	max_height;
	size_t	max_width;

	max_height = (HEIGHT - 128) / 64;
	max_width = (WIDTH + 64) / 64;
	line = get_next_line(game->fd);
	while (line != NULL)
	{
		game->line = str_free_to_join(game->line, line);
		if (!game->line)
		{
			free(line);
			return (1);
		}
		(*count_line)++;
		if (max_height < *count_line || max_width < ft_strlen(line))
		{
			ft_putstr_fd("Error\nMap too large for screen resolution\n", 2);
			return (1);
		}
		free(line);
		line = get_next_line(game->fd);
	}
	return (0);
}

int	create_map(t_game *game)
{
	size_t	i;

	i = 0;
	game->line = ft_strdup("");
	if (!game->line)
		return (1);
	game->fd = open(game->map_path, O_RDONLY);
	if (game->fd < 0)
		return (1);
	if (read_map(game, &i) == 1)
		return (1);
	if (check_map_errors(game, i) == 1)
		return (1);
		
	game->map = ft_split(game->line, '\n');
	if (!game->map)
		return (1);
	game->count_line = i;
	free(game->line);
	game->line_len = ft_strlen(game->map[0]);
	return (0);
}

int	init_map(t_game *game)
{
	game->fd = open(game->map_path, O_RDONLY);
	if (game->fd < 0)
	{
		ft_putstr_fd("Error\nCannot open file\n", 2);
		return (1);
	}
	if (create_map(game) == 1)
	{
		free(game->line);
		return (1);
	}
	close(game->fd);
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

	ft_bzero(&game, sizeof(t_game));
	game.map_path = argv[1];
	if (argc != 2 || check_argv(game.map_path) == 1)
	{
		ft_putstr_fd("Error\nInvalid arguments\n", 2);
		return (1);
	}
	if (init_map(&game) == 1)
	{
		ft_putstr_fd("Error\nMap error\n", 2);
		return (1);
	}
	
	init_window(&game);
	return (0);
}
