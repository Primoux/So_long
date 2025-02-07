/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:54:01 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/07 19:23:02 by enchevri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

int	parsing(t_game *game)
{
	if (check_line_len(*game) == 1)
	{
		ft_printf("Error\nInvalid map: Lines have different lengths\n");
		return (1);
	}
	if (check_walls_up_down(game) == 1 || check_walls_left_right(game) == 1)
	{
		ft_printf("Error\nInvalid map: Wall configuration error\n");
		return (1);
	}
	if (check_char(game) == 1 || game->char_count.player_count != 1
		|| game->char_count.colectible_count < 1
		|| game->char_count.exit_count != 1)
	{
		ft_printf("Error\nInvalid char\n");
		return (1);
	}
	return (0);
}
