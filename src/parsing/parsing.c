/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:54:01 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/13 14:50:05 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <unistd.h>

int	parsing(t_game *game)
{
	if (check_line_len(*game) == 1)
	{
		ft_putendl_fd("Error\nInvalid line lengths\n", 2);
		return (1);
	}
	if (check_walls_up_down(game) == 1 || check_walls_left_right(game) == 1)
	{
		ft_putendl_fd("Error\nWall error\n", 2);
		return (1);
	}
	if (check_char(game) == 1)
	{
		ft_putendl_fd("Error\nInvalid characters\n", 2);
		return (1);
	}
	if (game->char_count.p_count != 1 || game->char_count.c_count < 1
		|| game->char_count.e_count != 1)
	{
		ft_putstr_fd("Error\nInvalid number of characters (P, C, or E)\n", 2);
		return (1);
	}
	return (0);
}
