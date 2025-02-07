/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:25:48 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/07 19:23:53 by enchevri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

size_t	char_count(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	char_compare(char c)
{
	size_t	i;

	i = 0;
	while (GOOD_CHAR[i])
	{
		ft_printf("CHAR = %c\nchar compare =%c\n", c, GOOD_CHAR[i]); //{DEBUG}
		if (GOOD_CHAR[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	check_char(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	game->char_count.player_count = 0;
	game->char_count.colectible_count = 0;
	game->char_count.exit_count = 0;
	while (y < game->count_line)
	{
		x = 0;
		while (x < game->line_len)
		{
			if (char_compare(game->map[y][x]) == 1)
				return (1);
			x++;
		}
		game->char_count.player_count += char_count(game->map[y], 'P');
		game->char_count.colectible_count += char_count(game->map[y], 'C');
		game->char_count.exit_count += char_count(game->map[y], 'E');
		y++;
	}
    
	return (0);
}
