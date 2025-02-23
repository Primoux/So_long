/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:00:32 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/23 14:01:59 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <fcntl.h>
#include <unistd.h>

static int	check_map_errors(t_game *game)
{
	if (game->line == NULL)
	{
		ft_putstr_fd("Error\nEmpty map\n", 2);
		return (1);
	}
	if (game->count_line < 3)
	{
		ft_putstr_fd("Error\nMap too small (minimum size: 3x4)\n", 2);
		return (1);
	}
	if (game->line[ft_strlen(game->line) - 1] == '\n')
	{
		ft_putstr_fd("Error\nMap ends with newline\n", 2);
		return (1);
	}
	if (ft_strnstr(game->line, "\n\n", ft_strlen(game->line)))
	{
		ft_putstr_fd("Error\nMap contains empty lines\n", 2);
		return (1);
	}
	return (0);
}

/// @brief Read the map using my GNL
/// @param t_game game pointer
/// @return 1 on error and 0 on clean finish
static int	read_map(t_game *game)
{
	char	*line;
	size_t	max_height;
	size_t	max_width;

	max_height = (HEIGHT - 128) / game->mlx.pixel_size;
	max_width = (WIDTH) / game->mlx.pixel_size;
	line = get_next_line(game->fd);
	while (line != NULL)
	{
		game->line = str_free_to_join(game->line, line);
		if (!game->line)
		{
			free(line);
			return (1);
		}
		game->count_line++;
		if (max_height < game->count_line || max_width < ft_strlen(line))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(game->fd);
	}
	return (0);
}

int	create_map(t_game *game)
{
	game->count_line = 0;
	game->mlx.pixel_size = 64;
	game->line = ft_strdup("");
	if (!game->line)
		return (1);
	if (read_map(game) == 1)
	{
		ft_putstr_fd
		("Error\nMap too large for screen resolution(Or malloc fail)\n", 2);
		return (1);
	}
	if (check_map_errors(game) == 1)
		return (1);
	game->map = ft_split(game->line, '\n');
	if (!game->map)
	{
		ft_putstr_fd("Error\nSplit Failed\n", 2);
		return (1);
	}
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
	if (parsing(game) == 1)
	{
		free_tab(game->map);
		return (1);
	}
	close(game->fd);
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
		close(game.fd);
		return (1);
	}
	if (check_map_valid(&game) == 1)
	{
		cleanup_game(&game);
		free_tab(game.map);
		exit(EXIT_FAILURE);
	}
	init_window(&game);
	return (0);
}
