/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:00:32 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/03 19:13:33 by enchevri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"
#include <fcntl.h>

int	check_if_rectangle(int i, char *argv)
{
	int		fd;
	void	*line;
	char	**map;

	map = ft_calloc(i, sizeof(char));
	fd = open(argv, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		free(line);
		if (line == NULL)
			break ;
	}
}

int	init_map(int fd, char *argv)
{
	void	*line;
	int		i;

	ft_printf("%s\n", argv);
	i = 0;
	line = get_next_line(fd);
	while (1)
	{
		if (line == NULL)
			break ;
		i++;
		line = get_next_line(fd);
		free(line);
	}
	close(fd);
	if (i < 4)
		return (1);
	check_if_rectangle(i, argv);
	return (i);
}

int	init_game(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error opening the file\n");
		return (1);
	}
	if (init_map(fd, argv) == 1)
	{
		ft_printf("Map too small");
	}
	return (0);
}

int	main(int argc, char **argv)
{
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
	init_game(argv[1]);
}
