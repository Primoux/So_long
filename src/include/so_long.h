/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:45:04 by enchevri          #+#    #+#             */
/*   Updated: 2025/02/04 20:51:25 by enchevri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_game
{
	char	*map_path;
	int		count_line;
	int		fd;
	size_t		line_len;
	int		mlx;
	int		win;
	char	**map;
}			t_game;

#endif