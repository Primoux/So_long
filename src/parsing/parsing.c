/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:54:01 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/11 15:11:40 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <unistd.h>

int	parsing(t_game *game)
{
	if (check_line_len(*game) == 1)
	{
		ft_printf("Error: Invalid line lengths\n");
		return (1);
	}
	if (check_walls_up_down(game) == 1 || check_walls_left_right(game) == 1)
	{
		ft_printf("Error: Wall error\n");
		return (1);
	}
	if (check_char(game) == 1)
	{
		ft_printf("Error: Invalid characters\n");
		return (1);
	}
	if (game->char_count.p_count != 1 || game->char_count.c_count < 1
		|| game->char_count.e_count != 1)
	{
		ft_printf("Error\nP(%d)\nC(%d)\nE(%d)\n", game->char_count.p_count,
			game->char_count.c_count, game->char_count.e_count);
		return (1);
	}
	close(game->fd);
	return (0);
}
