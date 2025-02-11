/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:25:48 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/09 17:44:16 by enchevri         ###   ########lyon.fr   */
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
	game->char_count.p_count = 0;
	game->char_count.c_count = 0;
	game->char_count.e_count = 0;
	while (y < game->count_line)
	{
		x = 0;
		while (x < game->line_len)
		{
			if (char_compare(game->map[y][x]) == 1)
				return (1);
			x++;
		}
		game->char_count.p_count += char_count(game->map[y], 'P');
		game->char_count.c_count += char_count(game->map[y], 'C');
		game->char_count.e_count += char_count(game->map[y], 'E');
		y++;
	}
	return (0);
}
