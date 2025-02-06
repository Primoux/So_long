/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:00:32 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/06 21:05:20 by enchevri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <fcntl.h>
#include <unistd.h>


char *str_free_to_join(char *s1, char *s2)
{
	char *temp;
	

	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}

int	create_map(t_game *game)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	game->line = ft_strdup("\0");
	game->fd = open(game->map_path, O_RDONLY);
	if (game->fd < 0)
		return (1);
	line = get_next_line(game->fd);
	while (line != NULL)
	{
		game->line = str_free_to_join(game->line, line);
		free(line);
		line = get_next_line(game->fd);
	}
	game->map = ft_split(game->line, '\n');
	free(game->line);
	return (0);
}

int	init_game(t_game *game)
{
	game->fd = open(game->map_path, O_RDONLY);
	if (game->fd < 0)
	{
		ft_printf("Error opening the file\n");
		return (1);
	}
	if (create_map(game) == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc < 2)
	{
		ft_printf("No args\n");
		return (1);
	}
	if (argc > 2)
	{
		ft_printf("Too much args\n");
		return (1);
	}
	game.map_path = argv[1];
	init_game(&game);
	aff_map(game);
	free_tab(game.map);
}
