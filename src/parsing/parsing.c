/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:00:32 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/04 21:22:05 by enchevri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <fcntl.h>
#include <unistd.h>

char	*get_keyboard(void)
{
	int		fd;
	char	*line;

	fd = open("/etc/default/keyboard", O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error opening the keyboard\n");
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL && !(ft_strnstr(line, "LAYOUT", ft_strlen(line))))
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
	}
	if (line)
	{
		if (line[11] == 'u' && line[12] == 's')
			ft_printf("US\n");
		free(line);
	}
	close(fd);
	return (0);
}

int	check_if_rectangle(t_game game)
{
	void	*line;
	int		i;

	i = 0;
	game.fd = open(game.map_path, O_RDONLY);
	while (1)
	{
		line = get_next_line(game.fd);
		if (line == NULL)
			break ;
		ft_printf("%d\n", i++);
		if (game.line_len != ft_strlen(line) && game.line_len < 3)
		{
			ft_printf("line len %d et %d", game.line_len, ft_strlen(line));
			free(line);
			return (1);
		}
		game.line_len = ft_strlen(line);
		free(line);
	}
	return (0);
}

int	count_line_map(t_game game)
{
	void	*line;

	ft_printf("%s\n", game.map_path); // DEBUG
	line = get_next_line(game.fd);
	while (1)
	{
		if (line == NULL)
			break ;
		game.count_line++;
		line = get_next_line(game.fd);
		free(line);
	}
	close(game.fd);
	if (game.count_line < 4)
		return (1);
	check_if_rectangle(game);
	return (game.count_line);
}

int	init_game(t_game game)
{
	game.fd = open(game.map_path, O_RDONLY);
	if (game.fd < 0)
	{
		ft_printf("Error opening the file\n");
		return (1);
	}
	if (count_line_map(game) == 1)
	{
		ft_printf("Map too small");
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_printf("%d\n", get_keyboard());
	// if (argc < 2)
	// {
	// 	ft_printf("No args\n");
	// 	return (1);
	// }
	// if (argc > 2)
	// {
	// 	ft_printf("Too much args\n");
	// 	return (1);
	// }
	// game.map_path = argv[1];
	// init_game(game);
}
